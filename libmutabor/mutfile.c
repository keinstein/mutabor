/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: mutfile.c,v 1.1 2005/11/03 14:58:11 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:58:11 $
 * \version $Revision: 1.1 $
 *
 * $Log: mutfile.c,v $
 * Revision 1.1  2005/11/03 14:58:11  keinstein
 * initial release
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
#include "mutabor/mutfile.h"
#include "mutabor/mutfile.hh"
#include "mutabor/bad_decl.h"
#include "mutabor/mut_tab.h"
#include "mutabor/interval.h"
#include "mutabor/intervalPlaceholder.h"
#include "mutabor/ptrlist.h"
#include "mutabor/errors.h"
#include "mut.h"
#undef self
#include "mutlex.h"

/** Constructor for class object. Does nothing than error checking. */
extern void * MUTABOR_CLASS_FUNCTION(object,constructor)(void * _self);

void * MUTABOR_CLASS_FUNCTION(mutfile,constructor)(void * _self)
{
	MUT_CLASS(mutfile) * self;
	self = MUTABOR_CLASS_FUNCTION(object,constructor)(_self);
	CHK_CLASS(_self,mutfile);
	
	self->intervals=MUT_NEW(idlist);
	self->interval_placeholder=MUT_NEW(idlist);
	self->filename=NULL;
	self->descriptor=NULL;
	self->scanner=NULL;
	
	return (_self);
}

/** Destructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(mutfile, destructor)(void * _self) 
{
	MUT_CLASS(mutfile) * self=_self;
	CHK_CLASS(_self,mutfile);

	mutabor_delete(self->intervals);
	mutabor_delete(self->interval_placeholder);

	if (self->scanner) {
	  mutabor_parser_lex_destroy(self->scanner);
	}
  
	free(self->filename);
	if (self-> descriptor) {
		if (fclose(self->descriptor)) return NULL;
	}
	return (_self);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(mutfile,tostring)(void * _self)
{
	MUT_VIRTTABLE(object) ** self=_self;
	MUT_CLASS(mutfile) * oself=_self;
	char * data,*s1,*s2;
	CHK_CLASS(_self,mutfile);

	s1=MUT_VIRTCALL(idlist,oself->intervals,tostring)(oself->intervals);
	s2=MUT_VIRTCALL(idlist,oself->interval_placeholder,tostring)(oself->interval_placeholder);
	
	if (asprintf(&data,"%s (%p): %s %p\n->%s\n->%s",
		     (*self)->name, 
		     (void *)*self,
		     ((MUT_CLASS(mutfile)*) _self)->filename,
		     _self,s1,s2)){
		free(s1);free(s2);
		return data;
	}
	else {
		free(s1);free(s2);
		return NULL;
	}
}

void MUTABOR_CLASS_FUNCTION(mutfile,setfilename)(void * _self,char * name)
{
	CHK_CLASS(_self,mutfile);
	MUT_VALUE(mutfile,_self)->filename=strdup(name);
}

void MUTABOR_CLASS_FUNCTION(mutfile,parse)(void * _self)
{
	MUT_CLASS(mutfile) * self=_self;
	FILE * table;
	CHK_CLASS(_self,mutfile);

	/* setting up Mutabor file */
	assert(self->filename);
	if(!self->filename) 
		return;
	if (!self->descriptor) {
	  self->descriptor = fopen(self->filename,"r");
	  if (!self->descriptor) return;
	}
	/* setting up scanner */
	if(!self->scanner) 
		if (mutabor_parser_lex_init((void *) &(self->scanner))) 
			return;
	if ((table=fopen(mutabor_parser_get_table_filename("mutlex_de.tab"),"r"))) {
		mutabor_parser_tables_fload(table,self->scanner);
		fclose(table);
	} else return;
	mutabor_parser_set_in(self->descriptor,self->scanner);
	mutabor_parser_parse(_self);
	mutabor_parser_tables_destroy(self->scanner);
	mutabor_parser_lex_destroy(self->scanner);
	self->scanner=NULL;
	if (feof(self->descriptor)) 
	  if (!fclose(self->descriptor)) self->descriptor=NULL;
}

void * MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(void * _self,void * interval) 
{
	MUT_CLASS(mutfile) * self=_self;
	CHK_CLASS(_self,mutfile);
	CHK_CLASS(interval,interval);
	MUT_VIRTCALL(idlist,self->intervals,insert)(self->intervals,interval);
	return interval;
}

/** searches the interval list for a given identifier. 
 * \param _self current \c mutfile class.
 * \param name name of the intervall to search. It won't be deleted.
 * \return interval or new created alias to the interval if interval doesn't exist yet.
 */
void * MUTABOR_CLASS_FUNCTION(mutfile,get_interval)(void * _self,char * name)
{
	MUT_CLASS(mutfile) * self=_self;
	void * interval;
	CHK_CLASS(_self,mutfile);
	if ((interval=MUT_VIRTCALL(idlist,self->intervals,find)
	     (self->intervals,name))) {
		return interval;
	}
	if ((interval=MUT_VIRTCALL(idlist,self->interval_placeholder,find)
	     (self->interval_placeholder,name))) {
		return interval;
	}
	interval = MUT_NEW(intervalPlaceholder);
	MUTABOR_CLASS_FUNCTION(identifier,copy_name)(interval,name);
	MUT_VIRTCALL(idlist,self->interval_placeholder,insert)
		(self->interval_placeholder,interval);
	return interval;
}

void * MUTABOR_CLASS_FUNCTION(mutfile,check_interval)
                              (void * _self,void * _interval,char * name)
{
	MUT_CLASS(mutfile) * self=_self;
	MUT_CLASS(interval) * interval=_interval;
	MUT_CLASS(intervalPlaceholder) * placeholder;
	CHK_CLASS(_self,mutfile);
	CHK_CLASS(_interval,interval);
	if (MUT_VIRTCALL(idlist,self->intervals,find)(self->intervals,name)){
		return interval;
	}
	MUTABOR_CLASS_FUNCTION(identifier,set_name)(_interval,name);
	MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(self->intervals,1);
	if ((placeholder=(void *) 
	     MUT_VIRTCALL(idlist,self->interval_placeholder,find)
	     ((void *)self->interval_placeholder,name))) {
		MUT_CLASS(ptrlist) * ptrlist=MUT_NEW(ptrlist);
		if(!MUT_VIRTCALL(identifier,interval,check_cycle)
		   (interval,placeholder,ptrlist)) {
			MUTABOR_CLASS_FUNCTION(intervalPlaceholder,
					       setreplacement)
			(placeholder,_interval);
		}
		else fatal_error(MUTABOR_ERROR_INTERVAL_DEPENDENCY,name,name);
		mutabor_delete(ptrlist);
 	}
	return NULL;
}

