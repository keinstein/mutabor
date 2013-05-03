/** \file
 ********************************************************************
 * Zu korrigierende Querabhängigkeiten zur GUI und sonstige komische
 * Deklarationen.
 *
 * $Id: bad_decl.h,v 1.3 2005/11/03 14:27:26 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:27:26 $
 * \version $Revision: 1.3 $
 *
 * $Log: bad_decl.h,v $
 * Revision 1.3  2005/11/03 14:27:26  keinstein
 * new file header
 * includes corrected
 * MUTABOR_FLOAT
 * isnan asprintf strdup stpcpy fileno defined if strict ANSI on GCC
 *
 ********************************************************************/

#ifndef __BAD_DECL_H_INCLUDED
#define __BAD_DECL_H_INCLUDED

#include<math.h>
#ifdef __STRICT_ANSI__
#ifdef __GNUC__
#include <stdio.h>

#define isnan(a) (a==log(-1))
extern int asprintf (char **__restrict __ptr,
                     __const char *__restrict __fmt, ...)
     __THROW __attribute__ ((__format__ (__printf__, 2, 3)));

/* Duplicate S, returning an identical malloc'd string.  */
extern char *strdup (__const char *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
extern char *__stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __THROW __nonnull ((1, 2));
extern char *stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Return the system file descriptor for STREAM.  */
extern int fileno (FILE *__stream) __THROW;
#endif
#endif

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

#define bool unsigned int
#define MAX_BOX 256   /**< Maximale Anzahl der Boxen/Instumente */

    void fatal_error( int nummer, ... );
    void show_line_number( int n );
    void compiler_warning( int nummer, ... );
 
    extern int keys_changed[MAX_BOX];

#define GERMAN

    /** Maximale Breite eines Tonsystems */
#define MAX_BREITE 72
    
    /** Maximale Anzahl Bytes in MIDIOUT / MIDIIN */
#define MAX_MIDI 32

#define MUTABOR_FLOAT double
#define MUTABOR_FLOAT_FACTOR_COMPARE(a,b) (a>b?1:a==b?0:-1)
#define MUTABOR_FLOAT_DIVIDE(a,b) ((MUTABOR_FLOAT)a / (MUTABOR_FLOAT)b)
#define MUTABOR_FLOAT_MULTIPLY(a,b) ((MUTABOR_FLOAT)a / (MUTABOR_FLOAT)b)
#define MUTABOR_FLOAT_POW(a,b) (pow((MUTABOR_FLOAT)a,(MUTABOR_FLOAT)b))
  
#define mutabor_parser_get_table_filename(a) "../" a
#ifdef __cplusplus 
  }
}
#endif

#endif /* __BAD_DECL_H_INCLUDED */
