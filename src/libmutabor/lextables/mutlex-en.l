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
\#[A-Fa-f0-9]+    sscanf(yytext+1,"%x",&yylval.integer); return INTEGER;
INTERVAL          yylval.identifier = yytext; return INTERVALL;
ROOT              yylval.identifier = yytext; return WURZEL;
TONE              yylval.identifier = yytext; return TON;
TONESYSTEM        yylval.identifier = yytext; return TONSYSTEM;
RETUNING          yylval.identifier = yytext; return UMSTIMMUNG;
PATTERN           yylval.identifier = yytext; return HARMONIE;
LOGIC             yylval.identifier = yytext; return LOGIK;
SHIFTED           yylval.identifier = yytext; return FORM;
MIDICHANNEL       yylval.identifier = yytext; return INSTRUMENT;
KEY               yylval.identifier = yytext; return TASTE;
MIDIIN            yylval.identifier = yytext; return MIDI_IN;
MIDIOUT           yylval.identifier = yytext; return MIDI_OUT;
ELSE              yylval.identifier = yytext; return ANSONSTEN;
[[:alpha:]_']*    yylval.identifier = yytext; return IDENTIFIER;
[-+/[\]*:=(),~@<>{};]     return yytext[0]; 
[ \t\n]           /* Leerzeichen ignorieren  */;
.                 fatal_error(2,c,yylloc.first_line + 1); 
%%
