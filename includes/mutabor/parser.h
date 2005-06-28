/** \file
 ********************************************************************
 * Mutabor-Datei-Parser.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __PARSER_H_INCLUDED
#define __PARSER_H_INCLUDED

#include "mutabor/midicalc.h"
#include "mutabor/argument.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


void mutabor_programm_einlesen (char * filename) ;

extern FILE * quelldatei;
extern long anzahl_eingelesene_zeichen;

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __PARSER_H_INCLUDED */
