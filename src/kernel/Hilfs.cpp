/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Hilfs.cpp,v 1.6 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: Hilfs.cpp,v $
 * Revision 1.6  2011/02/20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Heapverwaltung
// ------------------------------------------------------------------

#include "Global.h"
#include "Execute.h"
#include "Parser.h"
#include "Hilfs.h"
#include "box.h"

#ifdef _
#undef _
#endif
#define _ _mut


#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif
#undef ACS_VERSION

#if 0
char SeRiEnNuMmEr[] = { 4,3,70,2,11,61,
                        127
                      };


static int the_character, is_valid;

int  intern_fgetc( FILE *stream )
{
	int zeichen;

	if (is_valid) {
		is_valid = 0;
		DEBUGLOG2(other,_T("old character: %x"),the_character);
		return  the_character;
	}

	zeichen = fgetc(stream);

	DEBUGLOG2(other,_T("new character: %x, EOF %d"),zeichen,feof(stream));
	return zeichen;
}

//#pragma warn -par
int  intern_ungetc( int c, FILE *stream )
{
	SeRiEnNuMmEr[0] = the_character;
	is_valid = 1;
	the_character = c;
	return 0;
}

//#pragma warn .par
#endif
/************************************

nur wenn alloca nicht da ist !

*************************************/

void * xalloca (mutabor_box_type * box, size_t size)
{
#ifdef ACS_VERSION
	void * help = Ax_malloc (size);
#else
	void * help = malloc (size);
#endif

	if (help == NULL) {
		DEBUGLOG2(other,_T("malloc(%d) failed."),(int)size);
		mutabor_error_message (box,
				       true, 
				       _("Not enough memory or too few data for mutabor in source file"));
				       
		return NULL;
	}

	return help;
}

void xde_alloca (void * pointer)

{
#ifdef ACS_VERSION
	Ax_ifree (pointer);
#else
	free (pointer);
#endif
}


/********************************************************

    Management of two heaps that can be deleted at once.

*****************************************************/

struct heap_element
{
	char inhalt [HEAP_PORTION_SYNTAX] ;
	size_t anzahl_belegt;

	struct heap_element * next;
};

#define OFFSET (sizeof(size_t))




//#pragma warn -par
void xfree (void * pointer)
{
	/* Nichts, wenn eigene Speicherverwaltung */

	/*   free (pointer); */
}

//#pragma warn .par

void * xmalloc (mutabor_box_type * box, size_t size)
{
	if (size + OFFSET > HEAP_PORTION_SYNTAX) {
		DEBUGLOG2(other,_T("Error: %d + %d > %d"),(int)size,(int)OFFSET, HEAP_PORTION_SYNTAX);
		mutabor_error_message(box,
				      false,
				      _("A chunk of memory has been requested that was too large (%d > %d)"),
				      (int)size,
				      (int)HEAP_PORTION_SYNTAX-size);

		return NULL;
	}

	if (box->file->heap.syntax_heap == NULL) {
#ifdef ACS_VERSION

		box->file->heap.syntax_heap = Ax_malloc (sizeof (struct heap_element));
		memset(box->file->heap.syntax_heap,0,sizeof (struct heap_element));
#else

		box->file->heap.syntax_heap = (heap_element*) calloc (1,sizeof (struct heap_element));
#endif

		if (box->file->heap.syntax_heap == NULL) {
			DEBUGLOG2(other,_T("calloc(1,%d) failed"),
			          (int)sizeof (struct heap_element));
			mutabor_error_message(box,
					      false,
					      _("Could not allocate syntax heap chunk."));
			return NULL;
		}

		box->file->heap.heap_to_use_syntax = box->file->heap.syntax_heap;

		box->file->heap.heap_to_use_syntax -> anzahl_belegt = 0;
		box->file->heap.heap_to_use_syntax -> next = NULL;
	}

	/**** Jetzt ist zumindest ein Block da ******/

	if (box->file->heap.heap_to_use_syntax -> anzahl_belegt + size + OFFSET
	                < HEAP_PORTION_SYNTAX) {
		void * help = & (box->file->heap.heap_to_use_syntax ->
				 inhalt [ box->file->heap.heap_to_use_syntax -> anzahl_belegt + OFFSET ]) ;
		box->file->heap.heap_to_use_syntax -> anzahl_belegt += size + OFFSET;
		((size_t *)help) [ - 1 ] = size;
		return help;
	} else {
#ifdef ACS_VERSION

		box->file->heap.heap_to_use_syntax -> next = Ax_malloc (sizeof (struct heap_element));

		box->file->heap.memset(heap_to_use_syntax -> next,0,sizeof (struct heap_element));
#else

		box->file->heap.heap_to_use_syntax -> next = (heap_element*) calloc (1,sizeof (struct heap_element));
#endif

		if (box->file->heap.heap_to_use_syntax -> next == NULL) {
			DEBUGLOG2(other,_T("heap_to_use_syntax -> nex == NULL"));
			mutabor_error_message(box,
					      false,
					      _("Could not allocate syntax heap chunk."));
			return NULL;
		}
		
		box->file->heap.heap_to_use_syntax = box->file->heap.heap_to_use_syntax -> next;

		box->file->heap.heap_to_use_syntax -> next = NULL;
		box->file->heap.heap_to_use_syntax -> anzahl_belegt = size + OFFSET;
		{ 
			void * tmp = (void*)box->file->heap.heap_to_use_syntax -> inhalt;
			size_t * tmp2 = (size_t *) tmp;
			*tmp2 = size;
			/* Original code:
			 * (size_t *)&(heap_to_use_syntax -> inhalt [ 0 ]) = size; 
			 */
		}
		return & box->file->heap.heap_to_use_syntax -> inhalt [ OFFSET ] ;
	}
}

void * xrealloc (mutabor_box_type * box, void * block, size_t newsize)

{
	if ( ((size_t *)block) [ - 1 ] + (char*)block
	     == & (box->file->heap.heap_to_use_syntax ->
		   inhalt [box->file->heap.heap_to_use_syntax -> anzahl_belegt])
	     &&
	     (char*)block + newsize <
	     &(box->file->heap.heap_to_use_syntax -> inhalt [ HEAP_PORTION_SYNTAX ])) {

		/* Dann war block der vorherige xmalloc und es passt noch rein */

		box->file->heap.heap_to_use_syntax -> anzahl_belegt +=
		        newsize - ((size_t *)block) [ - 1 ] ;
		((size_t *)block) [ - 1 ] = newsize;
		return block;
	} else {
		void * help = xmalloc (box, newsize);

		if (help) {
			memmove (help, block, newsize);
			return help;
		} else {
			DEBUGLOG2(other,_T("xmalloc (%d) failed"),(int)newsize);
			mutabor_error_message (box,
					       true, 
					       _("Reallocation of memory failed."));
				       
			return NULL;
		}
	}
}


void * xcalloc (mutabor_box_type * box, size_t anzahl, size_t size)
{
	void * help = xmalloc (box, anzahl * size);

	if (help) {
		memset (help, 0, anzahl * size);
		return help;
	} else {
		DEBUGLOG2(other,_T("xmalloc(%d * %d) failed"),(int)anzahl,(int)size);
		mutabor_error_message (box,
				       true, 
				       _("Not enough memory."));
				       
		return NULL;
	}
}

int loesche_syntax_speicher ( mutabor_box_type * box)
{

	struct heap_element * lauf;

	if (!box || !box->file) return 0;

	lauf = box->file->heap.syntax_heap;
	while (lauf) {
		struct heap_element * help = lauf->next;
#ifdef ACS_VERSION
		Ax_ifree (lauf);
#else
		free (lauf);
#endif
		lauf = help;
	}

	box->file->heap.syntax_heap = NULL;
	box->file->heap.heap_to_use_syntax = NULL;
	return 0; /* 0=ok, 1=fehler */
}

int init_syntax_speicher ( mutabor_box_type * box )
{
	return loesche_syntax_speicher (box);
}

/***************************

   Der Laufzeit-heap hat nur wenige elemente

***************************/

struct mini_heap
{
	void * pointer;
	struct mini_heap * next;
};

//#pragma warn -par
void yfree (void * pointer)
{
	/* nix */
}

//#pragma warn .par

void * ymalloc (mutabor_box_type * box, size_t size)
{
#ifdef ACS_VERSION
	void * help1 = Ax_malloc (size);
#else
	void * help1 = malloc (size);
#endif

	struct mini_heap * help2 = (mini_heap*) malloc (sizeof (struct mini_heap));

	if (help1 == NULL || help2 == NULL) {
		DEBUGLOG2(other,_T("help1 == %p(%d) ; help2 == %p(%d)"),
		          help1,(int)size,(void*)help2,(int)sizeof(struct mini_heap));
		mutabor_error_message(box,false,
				      _("Not enough memory."));
		return NULL;
	}

	help2 -> pointer = help1;

	help2 -> next = box->runtime_heap;
	box->runtime_heap = help2;

	return help1;
}

void * yrealloc (mutabor_box_type * box, void * block, size_t newsize)

{
	void * help = ymalloc (box, newsize);
	memmove (help, block, newsize);
	return help;
}

void * ycalloc (mutabor_box_type * box, size_t anzahl, size_t size)
{
	void * help = ymalloc ( box, anzahl * size );
	memset (help, 0, anzahl * size);
	return help;
}




int init_laufzeit_speicher ( mutabor_box_type * box )
{
	return loesche_laufzeit_speicher (box);
}

int loesche_laufzeit_speicher ( mutabor_box_type * box )
{

	struct mini_heap * lauf = box->runtime_heap;

	while (lauf) {

		struct mini_heap * help = lauf;
#ifdef ACS_VERSION
		Ax_ifree (lauf -> pointer);
#else
		free (lauf -> pointer);
#endif

		lauf = lauf -> next;

#ifdef ACS_VERSION
		Ax_ifree (help);
#else
		free (help);
#endif

	}

	box->runtime_heap = NULL;

	return 0; /* 0=ok, 1=fehler */
}

#ifdef __cplusplus
		}
	}
}
#endif

///\}
