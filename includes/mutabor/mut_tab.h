/** \file
 ********************************************************************
 * Kopfdatei zu mut.c, welche aus mut.y erstellt wird.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/mut_tab.h,v 1.2 2005/07/08 14:56:50 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/08 14:56:50 $
 * \version $Revision: 1.2 $
 * $Log: mut_tab.h,v $
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
void init_yylex (void);
int yylex();
void yyerror(char *);
int yyparse ();
*/

int mutabor_parser_parse();
int mutabor_parser_lex();
void mutabor_parser_error(char *);
void init_mutabor_parser_lex(void);

#endif /* __MUT_TAB_H_INCLUDED */
