%option   8bit 
%option   warn 
%option   outfile="mutlex.c"
%option   header-file="mutlex.h" 
%option   tables-file="mutlex_de.tab"
/* %option   tables-verify */
%option   case-insensitive
%option   prefix="mutabor_parser_"
%option   noyywrap
/* %option   ecs
%option   full */
%option   verbose
%option   debug 
%option bison-bridge reentrant
%option bison-locations 
%option yylineno 

%{
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif
#ifdef HAVE_WINSOCK2_H
# include <winsock2.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif

#include "mut.h"
/*#include "mutlex.h"
*/
#undef yylloc
#undef yylval
#include "mutabor/bad_decl.h"
#include "mutabor/mutfile.h"

/*
#define YY_DECL int mutabor_parser_lex (YYSTYPE * yylval_param, \
		YYLTYPE * yylloc_param, void * _self )
*/

#define YY_USER_ACTION \
  if (yy_rule_can_match_eol[yy_act] && yycolumn==0) { \
    int yyl; \
    for (yyl=yyleng-1;yyl>=0 && yytext[yyl] != '\n' ;yyl--) ; \
    yycolumn=yyleng-yyl; \
  } else yycolumn += yyleng;
#define BUMP \
  yylloc->first_line = yylloc->last_line; \
  yylloc->first_column = yylloc->last_column; \
  yylloc->last_column = yycolumn; \
  yylloc->last_line = yylineno;
%}

%x string
%%
%{
/*  MUT_CLASS(mutfile) * self=_self; */
%}

\"                BEGIN(string);
<string>[^"]*     /* comment */
<string>\"        BUMP BEGIN(0);

[[:digit:]]*"."[[:digit:]]*   BUMP yylval->f_value = atof(yytext); return F_NUMBER;
[[:digit:]]*            BUMP yylval->integer = atoi(yytext); return INTEGER;
#[[:xdigit:]]+    BUMP sscanf(yytext+1,"%x",(unsigned int *) &(yylval->integer)); return INTEGER;
INTERVALL         BUMP return INTERVALL;
WURZEL            BUMP return WURZEL;
TON               BUMP  return TON;
TONSYSTEM         BUMP  return TONSYSTEM;
UMSTIMMUNG        BUMP  return UMSTIMMUNG;
HARMONIE          BUMP  return HARMONIE;
LOGIK             BUMP  return LOGIK;
FORM              BUMP  return FORM;
MIDIKANAL         BUMP  return INSTRUMENT;
TASTE             BUMP  return TASTE;
MIDIIN|MIDI\ EIN  BUMP  return MIDI_IN;
MIDIOUT|MIDI\ AUS BUMP  return MIDI_OUT;
ANSONSTEN         BUMP  return ANSONSTEN;
[[:alpha:]_'\x80-\xff][[:alpha:][:digit:]_'\x80-\xff]*    { 
                  BUMP yylval->identifier = strdup(yytext); 
                  return IDENTIFIER;
                  }
[-+/[\]*:=(),~@<>{};]     BUMP return yytext[0]; 
[[:space:]]       BUMP  /* Leerzeichen ignorieren  */
 .                fatal_error(2,yytext[0],yylloc->first_line + 1); 
%%
