/** \file
 ********************************************************************
 * Kopfdatei zu mut.c, welche aus mut.y erstellt wird.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/mut_tab.h,v 1.4 2005/11/03 14:34:30 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:34:30 $
 * \version $Revision: 1.4 $
 * $Log: mut_tab.h,v $
 * Revision 1.4  2005/11/03 14:34:30  keinstein
 * new parser calling convention
 *
 * Revision 1.3  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 * Revision 1.2  2005/07/08 14:56:50  keinstein
 * Neu:
 * 	Kopf
 *
 * Ersetze yy durch mutabor_parser_
 *
 ********************************************************************/

#ifndef __MUT_TAB_H_INCLUDED
#define __MUT_TAB_H_INCLUDED

#define LINE_DRAW_QUANTUM 17
/*
#include "mut.h"
*/
/*
void init_yylex (void);
int yylex();
void yyerror(char *);
int yyparse ();
*/

long anzahl_eingelesene_zeichen;

int mutabor_parser_parse(void * _self);
/*
int mutabor_parser_lex (YYSTYPE * yylval_param, YYLTYPE * yylloc_param, void * _self );
void mutabor_parser_error(YYLTYPE * locp, void * _self, char const *s);
*/

#endif /* __MUT_TAB_H_INCLUDED */
