/** \file
 ********************************************************************
 *  Heapverwaltung.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/heap.c,v 1.5 2005/07/20 11:51:59 keinstein Exp $
 * \author R.Krauße <krausze@users.berlios.de>
 * \date $Date: 2005/07/20 11:51:59 $
 * \version $Revision: 1.5 $
 * \bug fatal_error(...) muss von Oberfläche getrennt werden.
 * \todo Portabilisierung von: memmove
 *
 * $Log: heap.c,v $
 * Revision 1.5  2005/07/20 11:51:59  keinstein
 * CVS-Kopf
 * config.h
 *
 * Revision 1.4  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 ********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen für diese Datei:
   * HAVE_MEMMOVE 
   * malloc
   * size_t
   */
#endif

#include<stdlib.h>
#include<string.h>

#include "mutabor/heap.h"

#undef ACS_VERSION

char SeRiEnNuMmEr[] = { 4,3,70,2,11,61,
                        127
                      };


/** Zeichen und Flag, ob ein gecachetes Zeichen da ist. */
static int the_character, is_valid;

/** Spezielle Implementation von  \c fgetc. Es wird getestet, ob sich noch ein 
 * Zeichen im Zwischenspeicher befindet. In diesem Fall wird das Zeichen 
 * zurückgegeben und der Zwischenspeicher geleert.
 * Ansonsten wird ein neues Zeichen eingelesen.
 * \param stream Datei, von der das Zeichen eingelesen werden soll.
 * \return Ein zeichen aus dem Eingabestrom.
 */
int  intern_fgetc( FILE *stream )
{ int zeichen;
  if (is_valid) {
      is_valid = 0;
      return  the_character;
  }
  zeichen = fgetc(stream);
  return zeichen;
}

/** Spezielle Implementation von \c ungetc. Das Zeichen  im Zwischenspeicher
 * wird an Position 0 vom Seriennummer-Feld geschrieben und danach wird das
 * übergebene Zeichen \a c in den Zwischenspeicher gelegt. 
 * \param c Zeichen, das ,,zurückgeschrieben`` werden soll.
 * \param stream Datei, für das das Zurückschreiben stattfinden soll.
 * \warning Das gesamte Programm kann auf diese Art und Weise maximal ein Zeichen
 * zwischenspeichern. Bei weiteren Aufrufen wird das vorher gespeicherte Zeichen 
 * einfach überschrieben.
 */
#ifdef __BORLANDC__
#pragma warn -par
#endif
int  intern_ungetc( int c, FILE *stream )
{ 
	 SeRiEnNuMmEr[0] = the_character;
	 is_valid = 1;
	 the_character = c;
	 return 0;
}
#ifdef __BORLANDC__
#pragma warn .par
#endif

/************************************

nur wenn alloca nicht da ist ! 

*************************************/

/** Allokiert einen Speicherbereich und erzeugt im Fehlerfall einen fatalen Fehler.
 * \param size Größe des benötigten Speicherbereiches in \c chars.
 * \return Zeiger auf den Speicherbereich.
 */
void * xalloca (size_t size) {
#ifdef ACS_VERSION
	 void * help = Ax_malloc (size);
#else
    void * help = malloc (size);
#endif
if (help == NULL) {
		  fatal_error (4);
		  return NULL;
	 }
	 return help;
}

/** Gibt einen Speicherbereich wieder frei. 
 * \param pointer Zeiger auf den freizugebenden Speicherbereich.
 */
void xde_alloca (void * pointer) {
#ifdef ACS_VERSION
    Ax_ifree (pointer);
#else
    free (pointer);
#endif
}


/********************************************************
  
    Verwaltung von zwei eigenen Heaps,
    die am STÜCK gelöscht werden können ! 

*****************************************************/

/** Typ eines eigenen HEAPs. */
struct heap_element {
  char inhalt [HEAP_PORTION_SYNTAX] ; /**< Datenbereich. */
  size_t anzahl_belegt;  /** Größe des belegten Bereiches. */
  struct heap_element * next; /** Nächster Heap. */
};

/** Syntax-Heap. */
static struct heap_element * syntax_heap = NULL ;

/** Zeiger auf Syntax-Heap-Elemente. */
static struct heap_element * heap_to_use_syntax = NULL;

/** Größe eines Größentyps. */
#define OFFSET (sizeof(size_t))




#ifdef __BORLANDC__
#pragma warn -par
#endif
/** Freigeben oder auch nich. 
 * \param pointer Zeiger auf den Speicherbereich, der hier nicht freigegeben wird. */
void xfree (void * pointer)
{
 /* Nichts, wenn eigene Speicherverwaltung */

 /*   free (pointer); */
}
#ifdef __BORLANDC__
#pragma warn .par
#endif

/** Belegt einen Speicherbereich in der einfach verketteten Liste \c syntax_heap.
 * Gegebenenfalls wird ein neues Element angelegt.
 * \param size Anzahl der Zeichen (\c char), die belegt werden sollen.
 */
void * xmalloc (size_t size)
{  
    if (size + OFFSET > HEAP_PORTION_SYNTAX) {
        fatal_error (4);
        return NULL;
    }

    if (syntax_heap == NULL) {
#ifdef ACS_VERSION
		  syntax_heap = Ax_malloc (sizeof (struct heap_element));
        memset(syntax_heap,0,sizeof (struct heap_element));
#else
		  syntax_heap = (struct heap_element*) calloc (1,sizeof (struct heap_element));
#endif
		  if (syntax_heap == NULL) {
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
    }
    else {
#ifdef ACS_VERSION
        heap_to_use_syntax -> next = Ax_malloc (sizeof (struct heap_element));
        memset(heap_to_use_syntax -> next,0,sizeof (struct heap_element));
#else
        heap_to_use_syntax -> next = (struct heap_element*) 
	          calloc (1,sizeof (struct heap_element));
#endif
        if (heap_to_use_syntax -> next == NULL) {
            fatal_error (4);
            return NULL;
        }
        heap_to_use_syntax = heap_to_use_syntax -> next;
        heap_to_use_syntax -> next = NULL;
        heap_to_use_syntax -> anzahl_belegt = size + OFFSET;
        *(size_t *)&(heap_to_use_syntax -> inhalt [ 0 ]) = size;
        return & heap_to_use_syntax -> inhalt [ OFFSET ] ;
    }
}

/** Ändert die Größe eines aktuellen Speicherbereiches im privaten Syntax-Heap.
 * Im Fehlerfall wird ein fataler Fehler ausgelöst.
 * \param block Zeiger auf den Block, dessen Größe geändert werden soll.
 * \param newsize Neue Größe für den Block.
 */ 
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
    }
    else {
       void * help = xmalloc (newsize);
       if (help) {
           memmove (help, block, newsize);
           return help;
       }
       else {
           fatal_error (4);
           return NULL;
       }
   }
}

/** Fordert einen Speicherbereich vom Syntax-Heap an, der
 * \a anzahl * \a size Zeichen enthält.
 * \param anzahl Anzahl der Einheiten
 * \param size Größe einer Speichereinheit.
 */
void * xcalloc (size_t anzahl, size_t size)
{  void * help = xmalloc (anzahl * size);
   if (help) {
       memset (help, 0, anzahl * size);
       return help;
   }
   else {
       fatal_error (4);
       return NULL;
   }
}
	
/** Löscht den gesamten Syntax-Heap. Anschließend werden
 * die beiden Zeiger \c syntax_heap und \c heap_to_use 
 * auf \c NULL gesetzt.
 * \retval 0 kein Fehler 
 * \retval 1 Fehler
 */
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

/** Initialisiert den Syntax-Heap. 
 * \retval Rückgabewert vom Löschen. Siehe \c loesche_syntax_speicher.
 */
int init_syntax_speicher ( void )
{
  return loesche_syntax_speicher ();
}

/***************************
 
   Der Laufzeit-heap hat nur wenige elemente 
   
***************************/

/** Typ für den Laufzeit-Heap */
struct mini_heap {
    void * pointer;
    struct mini_heap * next;
};

/** Laufzeit-Heap */
static struct mini_heap * laufzeit_heap = NULL;

#ifdef __BORLANDC__
#pragma warn -par
#endif
/** Löscht \a pointer nicht vom Laufzeit-Heap. ;-).
 * \param pointer Zeiger auf den zu ,,löschenden`` Speicherbreich. */
void yfree (void * pointer) {
  /* nix */
}
#ifdef __BORLANDC__
#pragma warn .par
#endif

/** Fordert Speicher auf dem Laufzeit-Heap an. 
 * Dabei wird auf der Liste ein neues Element angelegt.
 * \param size Größe des Speicherbereiches in \c char-Einheiten.
 * \return Zeiger auf den Speicherbereich.
 */
void * ymalloc (size_t size) {
#ifdef ACS_VERSION
    void * help1 = Ax_malloc (size);
#else
    void * help1 = malloc (size);
#endif
    struct mini_heap * help2 = (struct mini_heap*) malloc (sizeof (struct mini_heap));
    
    if (help1 == NULL || help2 == NULL) {
        fatal_error (4);
        return NULL;
    }
    
    help2 -> pointer = help1;
    help2 -> next = laufzeit_heap;
    laufzeit_heap = help2;
    
    return help1;
}

/** Ändert die Größe eines Elementes auf dem Laufzeit-Heap. 
 * \param block Zeiger auf das zu ändernde Element.
 * \param newsize neue Größe
 * \return Zeiger auf das neue Element.
 * \warning es wird nicht geprüft, ob der neue Speicherbereich größer, als der alte ist. 
 * Das kann gegebenenfalls zu Speicherüberlauf-Fehlern führen.
 */
void * yrealloc (void * block, size_t newsize) {
    void * help = ymalloc (newsize);
    memmove (help, block, newsize);
    return help; 
}

/** Fordert eine Anzahl von Einheiten auf dem Laufzeit-Heap an. 
 * \param anzahl Anzahl der Speichereinheiten.
 * \param size Größe einer Einheit.
 * \return Speicherbereich.
 */
void * ycalloc (size_t anzahl, size_t size) {
    void * help = ymalloc ( anzahl * size );
    memset (help, 0, anzahl * size);
    return help;
}



/** Initialisiert (Löscht) den Laufzeit-Speicher. 
 * \retval 0 kein Fehler
 * \retval 1 Fehler
 */
int init_laufzeit_speicher ( void )
{
  return loesche_laufzeit_speicher ();
}

/** Löscht den Laufzeitspeicher 
 * \retval 0 kein Fehler
 * \retval 1 Fehler
 */
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


