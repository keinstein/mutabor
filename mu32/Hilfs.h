#ifndef MU32_HILFS_H
#define MU32_HILFS_H

#include <cstdio>

#define HEAP_PORTION_SYNTAX   /*65536L*/ 64000
#define HEAP_PORTION_LAUFZEIT /*65536L*/ 64000

int  intern_fgetc( FILE *stream );
int  intern_ungetc( int c, FILE *stream );

void xfree (void * pointer);
void * xmalloc (size_t size);
void * xrealloc (void * block, size_t newsize);
void * xcalloc (size_t anzahl, size_t size);

void yfree (void * pointer);
void * ymalloc (size_t size);
void * yrealloc (void * block, size_t newsize);
void * ycalloc (size_t anzahl, size_t size);

int loesche_syntax_speicher ( void );
int init_syntax_speicher ( void );
int init_laufzeit_speicher ( void );
int loesche_laufzeit_speicher ( void );
void * xalloca (size_t size);
void xde_alloca (void * pointer);

#endif /* MU32_HILFS_H */


