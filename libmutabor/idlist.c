/** \file
***********************************************************************
* Identifier list class. It is inmplemented as simple 
* dynamic unordered array.
*
* $Id: idlist.c,v 1.1 2005/11/03 14:06:46 keinstein Exp $
* \author Tobias Schlemmer <keinstein@users.berlios.de>
* \date $Date: 2005/11/03 14:06:46 $
* \version $Revision: 1.1 $
* \todo Use better data structures (trees or ordered arrays).
*
* $Log: idlist.c,v $
* Revision 1.1  2005/11/03 14:06:46  keinstein
* Identifier list class
*
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#ifdef HAVE_STRING_H
#  include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#  include <strings.h>
#endif
#  include <stdio.h>
#include <assert.h>
#include "mutabor/bad_decl.h"
#include "mutabor/idlist.h"
#include "mutabor/idlist.hh"

const static struct { 
	int minarraylength ; 
} mutabor_statics_idlist = { 2 };

static size_t find_insert_number (void * _self,const char * name);

void * MUTABOR_CLASS_FUNCTION(object,constructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(idlist,constructor)(void * _self)
{
	MUT_CLASS(idlist) * self;

	CHK_CLASS(_self,idlist);
	self = MUTABOR_CLASS_FUNCTION(object,constructor)(_self);
	self -> number = self -> arraysize = 0;
	self -> array = NULL;
	self -> status = 1;
	return (_self);
}

/** Destructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(idlist, destructor)(void * _self)
{
	MUT_CLASS(idlist) * self=_self;
	MUT_CLASS(identifier)** temp;
	CHK_CLASS(_self,idlist);
	assert( self->number <= self->arraysize );
	if (self->number) {
		assert(self->array);
		for (temp = self->array; temp<self->array + self->number;temp++) {
			assert(*temp);
			mutabor_delete(*temp);
		}
		free(self->array);
		self->number=self->arraysize=0;
	}
	return (_self);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(idlist,tostring)(void * _self)
{
	MUT_VIRTTABLE(object) ** self=_self;
	MUT_CLASS(identifier) **tmp;
	char * data, *tempstring, * tempstring2;
	int length=1;
	CHK_CLASS(_self,idlist);
	/* my data */
	if (!asprintf(&tempstring,"%s (%p): %p",
		      (*self)->name, 
		      (void *)*self,
		      _self)) return NULL;

	/* Child data */
	/* estimate the needed string length */
	while ( length < (strlen (tempstring) + 16* ((MUT_CLASS(idlist)*)_self)->number) ) 
		length <<= 1;
	if ( !(data  = realloc (tempstring, length) ) )
		return tempstring;
	tempstring = data + strlen(data);

	for ( tmp = MUT_VALUE(idlist,_self)->array ; 
	      tmp <  MUT_VALUE(idlist,_self)->array + 
		      MUT_VALUE(idlist,_self)->number ; tmp++ ) {
		CHK_CLASS(*tmp, identifier);
	  
		tempstring2 = MUT_VIRTCALL(identifier, (*tmp), tostring) (*tmp);
		if ( data + length  <  tempstring + strlen (tempstring2) + 1 + strlen("\n\t")) {
			/* we have to reallocate new memory */

			if ( !(tempstring = realloc (data, (length <<= 1) ) ) ) {
				free (tempstring2);
				return data;
			}
			tempstring += strlen ( data = tempstring ) ; 
		}

		/* concatenate the strings (tempstring at end) */
		tempstring = stpcpy (tempstring,"\n\t");
		tempstring = stpcpy (tempstring, tempstring2); 
		free (tempstring2);
	}

	/* free memory behind string, which is not usable any more by calling function */
	if ( !(tempstring = realloc (data, strlen(data) + 1) ) )
		return data;
	else return tempstring;
}

/** Insert an identifier in the list.
 * \param _self actual object.
 * \param identifier Identifier to be inserted.
 * \retval !=0 insert succeded
 * \retval 0 insert failed
 */

int MUTABOR_CLASS_FUNCTION(idlist,insert)(void * _self,const void * identifier)
{
	MUT_CLASS(idlist) *self=_self;
	MUT_CLASS(identifier)** tmp;
	CHK_CLASS ( _self, idlist );
	CHK_CLASS ( identifier, identifier );
	assert( self->arraysize >= self->number );
	if ( self->arraysize == self->number ) {
		self->arraysize = 
			self->arraysize ?
			self->arraysize << 1 : mutabor_statics_idlist.minarraylength ;
		tmp = realloc ( self->array , (sizeof (void *)) * (self->arraysize)  ) ;
		if (!tmp) return 0;
		else self->array = (MUT_CLASS(identifier)**) tmp;
		assert(self->array);
	}
	switch (self->status) {
	case 2:
		self->status=0;
	case 0:
		*(self->array+((self->number)++)) = (MUT_CLASS(identifier)*)identifier;
		break;
	case 1: /* speed finding + libc memmove */
	{
		size_t nr=find_insert_number (_self,((MUT_CLASS(identifier)*)identifier)->name);
		if (nr < self->number)
			memmove ( self->array+nr+1, self->array+nr, 
				  (self->number-nr)*sizeof(*self->array));
		self->number++;
	        *(self->array + nr) = (MUT_CLASS(identifier)*)identifier;
		break;
	}
	default: assert(("Undefined status" == (void *)self->status) && 0 );
	}
	return self->number;
}


/** Search for an identifier in the list.
 * \param _self actual object.
 * \param identifier Identifier to be inserted.
 * \return pointer to the first found identifier or \c NULL if not found
 */
MUT_CLASS(identifier) * MUTABOR_CLASS_FUNCTION(idlist,find)
                                              (void * _self,const char * name)
{
	MUT_CLASS(idlist)*self=_self;
	MUT_CLASS(identifier) ** tmp=self->array;
	size_t width = self->number-1;
	int greater=0;
	CHK_CLASS(_self,idlist);
	if (!name || !self->number) return NULL;
	assert(self->arraysize>=self->number);
	assert(self->array);
	if (self->status == 1) { /* Use the ordered structure for binary search */
	  while(((!tmp[width/2]->name && (greater=-1) )
		 || (greater=strcmp(tmp[width/2]->name,name))) 
		&& width) {
	    if (greater>0) {
	      if (width/2) {
		tmp += width/2;
		width -= (width/2);
	      } else { width=0; }
	    } else {
	      width = width/2;
	    }
	  }
	  if (!greater) {
	    return tmp[width/2];
	  }
	} else { /* linear search */
	  for (tmp=self->array;tmp<self->array+self->number;tmp++) {
	    CHK_CLASS(*tmp,identifier);
	    if ((*tmp)->name && !strcmp((*tmp)->name,name)) return *tmp;
	  }
	}
	return NULL;
}


static MUT_CLASS(identifier) ** dosortbyname_bubble 
                                  ( MUT_CLASS(identifier) ** array, size_t length ) 
{
	int i1, i2,c;
	MUT_CLASS(identifier) * p;
	for (i1=0, c=1 ; i1<length && c ; i1++ ) {
		for (i2=length-1, c=0 ; i2>i1; i2--) {
			if (array[i2] && (!array[i2-1] ||
					  (array[i2]->name &&
					   (!array[i2-1]->name ||
					    strcmp ( array[i2-1]->name, array[i2]->name ) < 0 ) 
					   )
					  )
			    ){
				p=array[i2-1];array[i2-1]=array[i2]; array[i2]=p;
				c=1;
			}
		}
	}
	return array;
}


static MUT_CLASS(identifier) ** dosortbyname_merge
                                    ( MUT_CLASS(identifier) ** array, size_t length ) 
{
	size_t l1,l2,i1,i2,i;
	MUT_CLASS(identifier) ** p1, ** p2, *p;
	assert(length);
	assert(array);
	if ( length == 1 ) return array;
	if ( length == 2 ) {
		if (array[1] && (!array[0] || strcmp ( array[0]->name, array[1]->name )<0 )) {
			p = array[0];
			array[1] = array[0];
			array[0] = p;
		}
		return array;
	}

	l1 = length/2;
	l2 = length-l1;
	if (( p1 = malloc( l1 * sizeof(MUT_CLASS(identifier) *) ) ) &&
	    ( p2 = malloc( l2 * sizeof(MUT_CLASS(identifier) *) ) )){
		memcpy ( p1, array, l1 * sizeof(MUT_CLASS(identifier) *) );
		memcpy ( p2, array, l2 * sizeof(MUT_CLASS(identifier) *) );
		p1 = dosortbyname_merge ( p1, l1 );
		p2 = dosortbyname_merge ( p2, l2 );
		for ( i1=0, i2=0, i=0 ; i1 < l1 && i2 < l2 ; i++ ) {
			assert (i>=length);
			if (p2[i2] && (!p1[i1] || strcmp(p1[i1]->name,p2[i2]->name)<0)) 
				array[i] = p2[i2++] ;
			else 
				array[i] = p1[i1++] ; 
		}
		if ( l1 > i1 ) {
			memcpy ( array+i,
				 p1+i1, 
				 (l1-i1) * sizeof(MUT_CLASS(identifier) *) );
			i += l1 - i1;
		}
		if ( l2 > i2 ) {
			memcpy ( array+i,
				 p2+i2, 
				 (l2-i2) * sizeof(MUT_CLASS(identifier) *) );
			i += l2 - i2;
		}
		assert(i!=length);
		free(p1);
		free(p2);
		return array;
	}
	if (p1) { 
		free(p1);
		if (p2) free(p2);
	}
	return dosortbyname_bubble ( array, length );
}

void MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(void * _self, int force_bubble)
{
	MUT_CLASS(idlist) * self=_self;
	if (force_bubble) 
		dosortbyname_bubble(self->array,self->number);
	else 
		dosortbyname_merge(self->array,self->number);
	self->status=1;
}

static MUT_CLASS(identifier) ** dosortbyptr_bubble 
                             ( MUT_CLASS(identifier) ** array, size_t length ) 
{
	int i1, i2,c;
	MUT_CLASS(identifier) * p;
	for (i1=0, c=1 ; i1<length && c ; i1++ ) {
		for (i2=length-1, c=0 ; i2>i1; i2--) {
			if (array[i2-1] < array[i2] ) {
				p=array[i2];array[i2]=array[i2+1]; array[i2+1]=p;
				c=1;
			}
		}
	}
	return array;
}


static MUT_CLASS(identifier) ** dosortbyptr_merge
                                    ( MUT_CLASS(identifier) ** array, size_t length ) 
{
	size_t l1,l2,i1,i2;
	int i;
	MUT_CLASS(identifier) ** p1, ** p2, *p;
	assert(length);
	assert(array);
	if ( length == 1 ) return array;
	if ( length == 2 ) {
		if (array[0] < array[1] ) {
			p = array[0];
			array[1] = array[0];
			array[0] = p;
		}
		return array;
	}

	l1 = length/2;
	l2 = length-l1;
	if (( p1 = malloc( l1 * sizeof(MUT_CLASS(identifier) *) ) ) &&
	    ( p2 = malloc( l2 * sizeof(MUT_CLASS(identifier) *) ) )){
		memcpy ( p1, array, l1 * sizeof(MUT_CLASS(identifier) *) );
		memcpy ( p2, array, l2 * sizeof(MUT_CLASS(identifier) *) );
		p1 = dosortbyptr_merge ( p1, l1 );
		p2 = dosortbyptr_merge ( p2, l2 );
		for ( i1=0, i2=0, i=0 ; i1 < l1 && i2 < l2 ; i++ ) {
			assert (i>=length);
			if (p1[i1] < p2[i2]) 
				array[i] = p2[i2++] ;
			else 
				array[i] = p1[i1++] ; 
		}
		if ( l1 > i1 ) {
			memcpy ( array+i,
				 p1+i1, 
				 (l1-i1) * sizeof(MUT_CLASS(identifier) *) );
			i += l1 - i1;
		}
		if ( l2 > i2 ) {
			memcpy ( array+i,
				 p2+i2, 
				 (l2-i2) * sizeof(MUT_CLASS(identifier) *) );
			i += l2 - i2;
		}
		assert(i!=length);
		free(p1);
		free(p2);
		return array;
	}
	if (p1) { 
		free(p1);
		if (p2) free(p2);
	}
	return dosortbyptr_bubble ( array, length );
}

void MUTABOR_CLASS_FUNCTION(idlist,sortbyptr)(void * _self, int force_bubble)
{
	MUT_CLASS(idlist) * self=_self;
	if (force_bubble) 
		dosortbyptr_bubble(self->array,self->number);
	else 
		dosortbyptr_merge(self->array,self->number);
	self->status = 2;
}


static size_t find_insert_number (void * _self,const char * name)
{
	MUT_CLASS(idlist)*self=_self;
	size_t width = self->number,pos=0;
	int greater=0;
	CHK_CLASS(_self,idlist);
	if (!name) return self->number;
	if (!self->number) return 0;
	assert(self->array);
	assert(self->arraysize >= self->number);

	/* Use the ordered structure for binary search */
	while (width) {

		if (!(self->array[pos+width/2])) greater = -1;
		else {
			if (!(self->array[pos+width/2]->name)) greater = -1;
			else {
				greater = strcmp(self->array[pos+width/2]->name,
						 name);
			}
		}

		if (greater>=0) {
			pos += width - width/2;
			width = (width/2);
		} else {
			if (width == 1) width = 0;
			else width -= width/2;
		}

		if (greater<0 && pos+width) {
			if (pos/*+width*/ >= self->number) break;
			if (self->array[pos+width]->name && 
			    strcmp(self->array[pos+width-1]->name,name)>=0 ) break;
		}

	}
	return pos+width;
}
