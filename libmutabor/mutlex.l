%option   8bit 
%option   warn 
%option   outfile="lex.yy.c"
%option   header-file="mutlex.h"
%option   tables-file="mutlex_de.tab"
%option   tables-verify
%option   case-insensitive
%option   prefix="mutabor_parser_"
%option   noyywrap
/* %option   ecs
%option   full */
%option   verbose
%option   debug
%option bison-bridge
%option bison-locations yylineno
/* bison-bridge */
/* option   bison-locations */
%{
#include "mut.h"
#include "stdio.h"
#include "mutabor/bad_decl.h"
%}

%x string
%%


\"                BEGIN(string);
<string>[^"]*     fprintf(stderr,yytext);
<string>\"        BEGIN(0);

[[:digit:]]*"."[[:digit:]]*   yylval->f_value = atof(yytext); return F_NUMBER;
[[:digit:]]*            yylval->integer = atoi(yytext); return INTEGER;
#[[:xdigit:]]+    sscanf(yytext+1,"%x",&(yylval->integer)); return INTEGER;
INTERVALL         yylval->identifier = strdup(yytext); return INTERVALL;
WURZEL            yylval->identifier = strdup(yytext); return WURZEL;
TON               yylval->identifier = strdup(yytext); return TON;
TONSYSTEM         yylval->identifier = strdup(yytext); return TONSYSTEM;
UMSTIMMUNG        yylval->identifier = strdup(yytext); return UMSTIMMUNG;
HARMONIE          yylval->identifier = strdup(yytext); return HARMONIE;
LOGIK             yylval->identifier = strdup(yytext); return LOGIK;
FORM              yylval->identifier = strdup(yytext); return FORM;
MIDIKANAL         yylval->identifier = strdup(yytext); return INSTRUMENT;
TASTE             yylval->identifier = strdup(yytext); return TASTE;
MIDIIN|MIDI\ EIN  yylval->identifier = strdup(yytext); return MIDI_IN;
MIDIOUT|MIDI\ AUS yylval->identifier = strdup(yytext); return MIDI_OUT;
ANSONSTEN         yylval->identifier = strdup(yytext); return ANSONSTEN;
[[:alpha:]_'\x80-\xff][[:alpha:][:digit:]_'\x80-\xff]*    fprintf(stderr,"\n%s\n",yytext); yylval->identifier = strdup(yytext); return IDENTIFIER;
[-+/[\]*:=(),~@<>{};]     return yytext[0]; 
[[:space:]]           /* Leerzeichen ignorieren  */
 .                 fatal_error(2,yytext[0],yylloc->first_line + 1); 
%%
