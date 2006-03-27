/** \file
 ********************************************************************
 * Kopfdatei zu mut.c, welche aus mut.y erstellt wird.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/mut_tab.h,v 1.5 2006/03/27 16:55:04 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2006/03/27 16:55:04 $
 * \version $Revision: 1.5 $
 * $Log: mut_tab.h,v $
 * Revision 1.5  2006/03/27 16:55:04  keinstein
 * headers reorganized, so that mutlex.h is no longer needed by muttab.{y,c}
 *
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

#include "mut.h"

/* for mutlex.h */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

long anzahl_eingelesene_zeichen;

extern int mutabor_parser_parse(void * _self);
extern int mutabor_parser_lex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);
/*
int mutabor_parser_lex (YYSTYPE * yylval_param, YYLTYPE * yylloc_param, void * _self );
void mutabor_parser_error(YYLTYPE * locp, void * _self, char const *s);
*/

#endif /* __MUT_TAB_H_INCLUDED */
