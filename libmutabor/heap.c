/** \file
 ********************************************************************
 *  Heapverwaltung.
 * \author R.Krau�e
 * \date 1997
 * \version 2.win
 ********************************************************************/

//#include "global.h"
//#include "grafkern.h"
#include "heap.h"
#undef ACS_VERSION

char SeRiEnNuMmEr[] = { 4,3,70,2,11,61,
                        127
                      };


/** Zeichen und Flag, ob ein gecachetes Zeichen da ist. */
static int the_character, is_valid;

/** Spezielle Implementation von  \c fgetc. Es wird getestet, ob sich noch ein 
 * Zeichen im Zwischenspeicher befindet. In diesem Fall wird das Zeichen 
 * zur�ckgegeben und der Zwischenspeicher geleert.
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
 * �bergebene Zeichen \a c in den Zwischenspeicher gelegt. 
 * \param c Zeichen, das ,,zur�ckgeschrieben`` werden soll.
 * \param stream Datei, f�r das das Zur�ckschreiben stattfinden soll.
 * \warning Das gesamte Programm kann auf diese Art und Weise maximal ein Zeichen
 * zwischenspeichern. Bei weiteren Aufrufen wird das vorher gespeicherte Zeichen 
 * einfach �berschrieben.
 */
#pragma warn -par
int  intern_ungetc( int c, FILE *stream )
{ 
	 SeRiEnNuMmEr[0] = the_character;
	 is_valid = 1;
	 the_character = c;
	 return 0;
}
#pragma warn .par

/************************************

nur wenn alloca nicht da ist ! 

*************************************/

/** Allokiert einen Speicherbereich und erzeugt im Fehlerfall einen fatalen Fehler.
 * \param size Gr��e des ben�tigten Speicherbereiches in \c chars.
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
    die am ST�CK gel�scht werden k�nnen ! 

*****************************************************/

/** Typ eines eigenen HEAPs. */
struct heap_element {
  char inhalt [HEAP_PORTION_SYNTAX] ; /**< Datenbereich. */
  size_t anzahl_belegt;  /** Gr��e des belegten Bereiches. */
  struct heap_element * next; /** N�chster Heap. */
};

/** Syntax-Heap. */
static struct heap_element * syntax_heap = NULL ;

/** Zeiger auf Syntax-Heap-Elemente. */
static struct heap_element * heap_to_use_syntax = NULL;

/** Gr��e eines Gr��entyps. */
#define OFFSET (sizeof(size_t))




#pragma warn -par
/** Freigeben oder auch nich. 
 * \param pointer Zeiger auf den Speicherbereich, der hier nicht freigegeben wird. */
void xfree (void * pointer)
{
 /* Nichts, wenn eigene Speicherverwaltung */

 /*   free (pointer); */
}
#pragma warn .par

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
		  syntax_heap = (heap_element*) calloc (1,sizeof (struct heap_element));
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
        heap_to_use_syntax -> next = (heap_element*) calloc (1,sizeof (struct heap_element));
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

/** �ndert die Gr��e eines aktuellen Speicherbereiches im privaten Syntax-Heap.
 * Im Fehlerfall wird ein fataler Fehler ausgel�st.
 * \param block Zeiger auf den Block, dessen Gr��e ge�ndert werden soll.
 * \param newsize Neue Gr��e f�r den Block.
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
 * \a anzahl * \a size Zeichen enth�lt.
 * \param anzahl Anzahl der Einheiten
 * \param size Gr��e einer Speichereinheit.
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
	
/** L�scht den gesamten Syntax-Heap. Anschlie�end werden
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
 * \retval R�ckgabewert vom L�schen. Siehe \c loesche_syntax_speicher.
 */
int init_syntax_speicher ( void )
{
  return loesche_syntax_speicher ();
}

/***************************
 
   Der Laufzeit-heap hat nur wenige elemente 
   
***************************/

/** Typ f�r den Laufzeit-Heap */
struct mini_heap {
    void * pointer;
    struct mini_heap * next;
};

/** Laufzeit-Heap */
static struct mini_heap * laufzeit_heap = NULL;

#pragma warn -par
/** L�scht \a pointer nicht vom Laufzeit-Heap. ;-).
 * \param pointer Zeiger auf den zu ,,l�schenden`` Speicherbreich. */
void yfree (void * pointer) {
  /* nix */
}
#pragma warn .par

/** Fordert Speicher auf dem Laufzeit-Heap an. 
 * Dabei wird auf der Liste ein neues Element angelegt.
 * \param size Gr��e des Speicherbereiches in \c char-Einheiten.
 * \return Zeiger auf den Speicherbereich.
 */
void * ymalloc (size_t size) {
#ifdef ACS_VERSION
    void * help1 = Ax_malloc (size);
#else
    void * help1 = malloc (size);
#endif
    struct mini_heap * help2 = (mini_heap*) malloc (sizeof (struct mini_heap));
    
    if (help1 == NULL || help2 == NULL) {
        fatal_error (4);
        return NULL;
    }
    
    help2 -> pointer = help1;
    help2 -> next = laufzeit_heap;
    laufzeit_heap = help2;
    
    return help1;
}

/** �ndert die Gr��e eines Elementes auf dem Laufzeit-Heap. 
 * \param block Zeiger auf das zu �ndernde Element.
 * \param newsize neue Gr��e
 * \return Zeiger auf das neue Element.
 * \warning es wird nicht gepr�ft, ob der neue Speicherbereich gr��er, als der alte ist. 
 * Das kann gegebenenfalls zu Speicher�berlauf-Fehlern f�hren.
 */
void * yrealloc (void * block, size_t newsize) {
    void * help = ymalloc (newsize);
    memmove (help, block, newsize);
    return help; 
}

/** Fordert eine Anzahl von Einheiten auf dem Laufzeit-Heap an. 
 * \param anzahl Anzahl der Speichereinheiten.
 * \param size Gr��e einer Einheit.
 * \return Speicherbereich.
 */
void * ycalloc (size_t anzahl, size_t size) {
    void * help = ymalloc ( anzahl * size );
    memset (help, 0, anzahl * size);
    return help;
}



/** Initialisiert (L�scht) den Laufzeit-Speicher. 
 * \retval 0 kein Fehler
 * \retval 1 Fehler
 */
int init_laufzeit_speicher ( void )
{
  return loesche_laufzeit_speicher ();
}

/** L�scht den Laufzeitspeicher 
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


