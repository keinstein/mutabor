/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Hilfs.h,v 1.6 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: Hilfs.h,v $
 * Revision 1.6  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-02-20 22:35:55  keinstein
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_Hilfs_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_Hilfs_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_Hilfs_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_Hilfs_H_PRECOMPILED
#define MU32_Hilfs_H_PRECOMPILED

// system headers which do seldom change
#include <stdio.h>

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


#endif /* MU32_HILFS_H_PRECOMPILED */

#endif /* MU32_HILFS_H */


///\}
