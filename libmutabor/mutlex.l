%option   8bit bison-bridge
%option   warn nodefault
%option   bison-locations
%option   outfile="mutlex.c"
%option   header-file="mutlex.h"
%option   tables-file="mutlex_de.tab"
%option   case-insensitive
%option   prefix="mutabor_parser_"
%option   noyywrap
%option   ecs
%option   full
%option   verbose
/* %options reentrant */

%{
#include "mut.h"
#define yylval mutabor_parser_lval
%}

%x string
%%

\"                BEGIN(string);
<string>[^"]*     /* ignoriere Kommentare */
<string>\"        BEGIN(0);

[0-9]*"."[0-9]*   yylval.f_value = atof(yytext); return F_NUMBER;
[0-9]*            yylval.integer = atoi(yytext); return INTEGER;
#[A-Fa-f0-9]+    sscanf(yytext+1,"%x",&yylval.integer); return INTEGER;
INTERVALL         yylval.identifier = yytext; return INTERVALL;
WURZEL            yylval.identifier = yytext; return WURZEL;
TON               yylval.identifier = yytext; return TON;
TONSYSTEM         yylval.identifier = yytext; return TONSYSTEM;
UMSTIMMUNG        yylval.identifier = yytext; return UMSTIMMUNG;
HARMONIE          yylval.identifier = yytext; return HARMONIE;
LOGIK             yylval.identifier = yytext; return LOGIK;
FORM              yylval.identifier = yytext; return FORM;
MIDIKANAL         yylval.identifier = yytext; return INSTRUMENT;
TASTE             yylval.identifier = yytext; return TASTE;
MIDIIN|MIDI\ EIN  yylval.identifier = yytext; return MIDI_IN;
MIDIOUT|MIDI\ AUS yylval.identifier = yytext; return MIDI_OUT;
ANSONSTEN         yylval.identifier = yytext; return ANSONSTEN;
[[:alpha:]_']*    yylval.identifier = yytext; return IDENTIFIER;
[-+/[\]*:=(),~@<>{};]     return yytext[0]; 
[ \t\n]           /* Leerzeichen ignorieren  */;
.                 fatal_error(2,c,yylloc.first_line + 1); 
%%
