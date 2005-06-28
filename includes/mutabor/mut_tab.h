/** \file
 ********************************************************************
 * Kopfdatei zu mut_tab.c, welche aus mut.y erstellt wird.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __MUT_TAB_H_INCLUDED
#define __MUT_TAB_H_INCLUDED

#define LINE_DRAW_QUANTUM 17

void init_yylex (void);
int yylex();
void yyerror(char *);
int yyparse ();


#endif /* __MUT_TAB_H_INCLUDED */
