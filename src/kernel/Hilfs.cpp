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
#include "GrafKern.h"
#include "Hilfs.h"
#undef ACS_VERSION

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

/************************************

nur wenn alloca nicht da ist !

*************************************/

void * xalloca (size_t size)
{
#ifdef ACS_VERSION
	void * help = Ax_malloc (size);
#else
	void * help = malloc (size);
#endif

	if (help == NULL) {
		DEBUGLOG2(other,_T("malloc(%d) failed."),(int)size);
		fatal_error (MUT_ERR_MALLOC_FAILED);
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

    Verwaltung von zwei eigenen Heaps,
    die am STšCK gel”scht werden k”nnen !

*****************************************************/

struct heap_element
{
	char inhalt [HEAP_PORTION_SYNTAX] ;
	size_t anzahl_belegt;

	struct heap_element * next;
};

static struct heap_element * syntax_heap = NULL ;

static struct heap_element * heap_to_use_syntax = NULL;

#define OFFSET (sizeof(size_t))




//#pragma warn -par
void xfree (void * pointer)
{
	/* Nichts, wenn eigene Speicherverwaltung */

	/*   free (pointer); */
}

//#pragma warn .par

void * xmalloc (size_t size)
{
	if (size + OFFSET > HEAP_PORTION_SYNTAX) {
		DEBUGLOG2(other,_T("Error: %d + %d > %d"),(int)size,(int)OFFSET, HEAP_PORTION_SYNTAX);
		fatal_error (4);
		return NULL;
	}

	if (syntax_heap == NULL) {
#ifdef ACS_VERSION

		syntax_heap = Ax_malloc (sizeof (struct heap_element));

		memset(syntax_heap,0,sizeof (struct heap_element));
#else

		syntax_heap = (heap_element*) calloc (1,sizeof (struct heap_element));
#endif

		if (syntax_heap == NULL) {
			DEBUGLOG2(other,_T("calloc(1,%d) failed"),
			          (int)sizeof (struct heap_element));
			fatal_error (4);
			return NULL;
		}

		heap_to_use_syntax = syntax_heap;

		heap_to_use_syntax -> anzahl_belegt = 0;
		heap_to_use_syntax -> next = NULL;
	}

	/**** Jetzt ist zumindest ein Block da ******/

	if (heap_to_use_syntax -> anzahl_belegt + size + OFFSET
	                < HEAP_PORTION_SYNTAX) {
		void * help = & heap_to_use_syntax ->
		              inhalt [ heap_to_use_syntax -> anzahl_belegt + OFFSET ] ;
		heap_to_use_syntax -> anzahl_belegt += size + OFFSET;
		((size_t *)help) [ - 1 ] = size;
		return help;
	} else {
#ifdef ACS_VERSION

		heap_to_use_syntax -> next = Ax_malloc (sizeof (struct heap_element));

		memset(heap_to_use_syntax -> next,0,sizeof (struct heap_element));
#else

		heap_to_use_syntax -> next = (heap_element*) calloc (1,sizeof (struct heap_element));
#endif

		if (heap_to_use_syntax -> next == NULL) {
			DEBUGLOG2(other,_T("heap_to_use_syntax -> nex == NULL"));
			fatal_error (4);
			return NULL;
		}

		heap_to_use_syntax = heap_to_use_syntax -> next;

		heap_to_use_syntax -> next = NULL;
		heap_to_use_syntax -> anzahl_belegt = size + OFFSET;
		{ 
			void * tmp = (void*)heap_to_use_syntax -> inhalt;
			size_t * tmp2 = (size_t *) tmp;
			*tmp2 = size;
			/* Original code:
			 * (size_t *)&(heap_to_use_syntax -> inhalt [ 0 ]) = size; 
			 */
		}
		return & heap_to_use_syntax -> inhalt [ OFFSET ] ;
	}
}

void * xrealloc (void * block, size_t newsize)

{
	if ( ((size_t *)block) [ - 1 ] + (char*)block
	                == & heap_to_use_syntax ->
	                inhalt [heap_to_use_syntax -> anzahl_belegt]
	                &&
	                (char*)block + newsize <
	                &(heap_to_use_syntax -> inhalt [ HEAP_PORTION_SYNTAX ])) {

		/* Dann war block der vorherige xmalloc und es passt noch rein */

		heap_to_use_syntax -> anzahl_belegt +=
		        newsize - ((size_t *)block) [ - 1 ] ;
		((size_t *)block) [ - 1 ] = newsize;
		return block;
	} else {
		void * help = xmalloc (newsize);

		if (help) {
			memmove (help, block, newsize);
			return help;
		} else {
			DEBUGLOG2(other,_T("xmalloc (%d) failed"),(int)newsize);
			fatal_error (4);
			return NULL;
		}
	}
}


void * xcalloc (size_t anzahl, size_t size)
{
	void * help = xmalloc (anzahl * size);

	if (help) {
		memset (help, 0, anzahl * size);
		return help;
	} else {
		DEBUGLOG2(other,_T("xmalloc(%d * %d) failed"),(int)anzahl,(int)size);
		fatal_error (4);
		return NULL;
	}
}

int loesche_syntax_speicher ( void )
{

	struct heap_element * lauf = syntax_heap;

	while (lauf) {

		struct heap_element * help = lauf->next;
#ifdef ACS_VERSION
		Ax_ifree (lauf);
#else
		free (lauf);
#endif
		lauf = help;
	}

	syntax_heap = NULL;

	heap_to_use_syntax = NULL;

	return 0; /* 0=ok, 1=fehler */
}

int init_syntax_speicher ( void )
{
	return loesche_syntax_speicher ();
}

/***************************

   Der Laufzeit-heap hat nur wenige elemente

***************************/

struct mini_heap
{
	void * pointer;

	struct mini_heap * next;
};

static struct mini_heap * laufzeit_heap = NULL;

//#pragma warn -par
void yfree (void * pointer)
{
	/* nix */
}

//#pragma warn .par

void * ymalloc (size_t size)
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
		fatal_error (4);
		return NULL;
	}

	help2 -> pointer = help1;

	help2 -> next = laufzeit_heap;
	laufzeit_heap = help2;

	return help1;
}

void * yrealloc (void * block, size_t newsize)

{
	void * help = ymalloc (newsize);
	memmove (help, block, newsize);
	return help;
}

void * ycalloc (size_t anzahl, size_t size)
{
	void * help = ymalloc ( anzahl * size );
	memset (help, 0, anzahl * size);
	return help;
}




int init_laufzeit_speicher ( void )
{
	return loesche_laufzeit_speicher ();
}

int loesche_laufzeit_speicher ( void )
{

	struct mini_heap * lauf = laufzeit_heap;

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

	laufzeit_heap = NULL;

	return 0; /* 0=ok, 1=fehler */
}



///\}
