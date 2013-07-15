%option   8bit 
%option   warn 
%option   case-insensitive
%option   noyywrap
%option   verbose
%option   debug
%option yyclass="mutabor_lexer"
%option yylineno 
%option prefix="mutabor_lexer_"

%{
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define YY_NO_UNISTD_H
#include "src/kernel/mut.hh"
#include "src/kernel/mutlex.h"

extern "C" inline int dummyisatty (int fd) { return isatty(fd); }
#define isatty dummyisatty
/*
#define BUMP \
  yylloc->first_line = yylloc->last_line; \
  yylloc->first_column = yylloc->last_column; \
  yylloc->last_column = yycolumn; \
  yylloc->last_line = yylineno;
*/
#define BUMP
%}

%x comment
%%
%{

%}

\"                BUMP BEGIN(comment); return MUTABOR_TOKEN_COMMENT_START;
<comment>[^"]*    BUMP /* comment */   return MUTABOR_TOKEN_COMMENT;
<comment>\"       BUMP BEGIN(0);       return MUTABOR_TOKEN_COMMENT_END;

[[:digit:]]*"."[[:digit:]]*   BUMP yylval->f_value = atof(yytext); return MUTABOR_TOKEN_F_NUMBER;
[[:digit:]]*            BUMP yylval->integer = atoi(yytext); return MUTABOR_TOKEN_INTEGER;
#[[:xdigit:]]+    BUMP sscanf(yytext+1,"%x",(unsigned int *) &(yylval->integer)); return MUTABOR_TOKEN_INTEGER;
INTERVALL?        BUMP return MUTABOR_TOKEN_INTERVAL;
WURZEL|ROOT       BUMP return MUTABOR_TOKEN_ROOT;
TONE?             BUMP  return MUTABOR_TOKEN_TONE;
TONE?SYSTEM       BUMP  return MUTABOR_TOKEN_TONESYSTEM;
UMSTIMMUNG|RETUNING    BUMP  return MUTABOR_TOKEN_RETUNING;
HARMON(Y|IE)      BUMP  return MUTABOR_TOKEN_HARMONY;
LOGI[KC]          BUMP  return MUTABOR_TOKEN_LOGIC;
FORM|PATTERN      BUMP  return MUTABOR_TOKEN_FORM;
MIDIKANAL|INSTRUMENT   BUMP  return MUTABOR_TOKEN_MIDICHANNEL;
TASTE|KEY         BUMP  return MUTABOR_TOKEN_KEY;
MIDIIN|MIDI\ EIN  BUMP  return MUTABOR_TOKEN_MIDI_IN;
MIDIOUT|MIDI\ AUS BUMP  return MUTABOR_TOKEN_MIDI_OUT;
ANSONSTEN|ELSE    BUMP  return MUTABOR_TOKEN_ELSE;
ABSTAND|DISTANCE  BUMP   { 
                  BUMP yylval->identifier = strdup(yytext);
                  return report_parameters?MUTABOR_TOKEN_PARAMETER:MUTABOR_TOKEN_IDENTIFIER;
                  }
[[:alpha:]_'\x80-\xff][[:alpha:][:digit:]_'\x80-\xff]*    { 
                  BUMP yylval->identifier = strdup(yytext);
                  return MUTABOR_TOKEN_IDENTIFIER;
                  }
->                BUMP  return MUTABOR_TOKEN_CALLS;
[-+/[\]*:=(),~@<>{};]     BUMP return yytext[0]; 
[[:space:]]+       BUMP  return MUTABOR_TOKEN_SPACES;
 .                BUMP  return MUTABOR_TOKEN_OTHER; /* fatal error */
%%
