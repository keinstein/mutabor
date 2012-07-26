/** \file
 ********************************************************************
 *  Heapverwaltung.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/heap.h,v 1.3 2005/07/19 15:15:27 keinstein Exp $
 * \author R.Krauße <krausze@users.berlios.de>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.3 $
 *
 * $Log: heap.h,v $
 * Revision 1.3  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 ********************************************************************/
#ifndef __HEAP_H_INCLUDED__
#define __HEAP_H_INCLUDED__7

#ifdef HAVE_CONFIG_H
#  include "config.h"
/* für size_t */
#endif

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif
    
#include<stdio.h>
#include "mutabor/bad_decl.h"

    /** Größe eines Syntax-Heap-Elementes.*/
#define HEAP_PORTION_SYNTAX   /*65536L*/ 64000
    /** Größe eine Laufzeit-Heap-Elementes. */
#define HEAP_PORTION_LAUFZEIT /*65536L*/ 64000
    
    /* #define alloca xmalloc */
#define bcopy(from,to,n) memcpy((to),(from),(n))
#define bzero(s,n) memset((s),0,(n))
#define bcmp(b1,b2,len) memcmp((b1),(b2),(len))

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

    int  intern_fgetc( FILE *stream );
    int  intern_ungetc( int c, FILE *stream );

    extern int geheimcode;

#ifdef __cplusplus
  }
}
#endif

#endif /* __HEAP_H_INCLUDED__ */
