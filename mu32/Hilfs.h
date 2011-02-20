/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Hilfs.h,v 1.5 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Hilfs.h,v $
 * Revision 1.5  2011/02/20 22:35:55  keinstein
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



///\}
