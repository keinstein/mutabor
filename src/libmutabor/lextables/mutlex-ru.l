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
ИНТЕРВАЛ          yylval.identifier = yytext; return INTERVALL;
КОРЕНЬ            yylval.identifier = yytext; return WURZEL;
ТОН               yylval.identifier = yytext; return TON;
СИСТЕМ\ ТОНОВ      yylval.identifier = yytext; return TONSYSTEM;
СТРОИТЬ           yylval.identifier = yytext; return UMSTIMMUNG;
ГАРМОНИЯ          yylval.identifier = yytext; return HARMONIE;
ЛОГИКА            yylval.identifier = yytext; return LOGIK;
ФОРМА             yylval.identifier = yytext; return FORM;
МИДИКАНАЛ         yylval.identifier = yytext; return INSTRUMENT;
КЛАВИША           yylval.identifier = yytext; return TASTE;
МИДИИН            yylval.identifier = yytext; return MIDI_IN;
МИДИАУТ           yylval.identifier = yytext; return MIDI_OUT;
ИНАЧЕ             yylval.identifier = yytext; return ANSONSTEN;
[[:alpha:]_']*    yylval.identifier = yytext; return IDENTIFIER;
[-+/[\]*:=(),~@<>{};]     return yytext[0]; 
[ \t\n]           /* Leerzeichen ignorieren  */;
.                 fatal_error(2,c,yylloc.first_line + 1); 
%%
