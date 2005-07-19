/** \file
 ******************************************************
 * Parser-Generator f¸r Mutabor-Dateien.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/mut.y,v 1.3 2005/07/19 15:15:27 keinstein Exp $
 * \author R¸diger Krauﬂe <krausze@users.berlios.de>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.3 $
 * $Log: mut.y,v $
 * Revision 1.3  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 * \todo Portabilisierung von: memmove, pow, limits.h
 ******************************************************
 */
%verbose
%locations
%pure-parser
%name-prefix="mutabor_parser_"
%token-table
/* Mutabor Tonsysteme */

%{

/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

#ifdef __BORLANDC__
#pragma warn -cln
#pragma warn -aus
#pragma warn -sig
#pragma warn -par
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen f¸r diese Datei:
   * HAVE_MEMMOVE 
   * HAVE_POW
   * HAVE_LIMITS_H
   * const
   * size_t
   */
#endif

#include <ctype.h>
#  ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "mut.h"
#include "mutabor/heap.h"
#include "mutabor/mut_tab.h"
#include "mutabor/ton.h"
#include "mutabor/interval.h"
#include "mutabor/tonsystem.h"
#include "mutabor/argument.h"
#include "mutabor/parameter.h"
#include "mutabor/umstimmung.h"
#include "mutabor/aktion.h"
#include "mutabor/taste.h"
#include "mutabor/harmonie.h"
#include "mutabor/ausloeser.h"
#include "mutabor/logik.h"
#include "mutabor/anweisung.h"
#include "mutabor/instrument.h"
#include "mutabor/parser.h"
#include "mutabor/errors.h"
#include "mutlex.h"

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line+1

#define alloca xmalloc
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */

%}

%union {
    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */
}

%token <identifier> IDENTIFIER
%token <f_value> F_NUMBER
%token <integer> INTEGER

%token INTERVALL
%token WURZEL
%token TON
%token TONSYSTEM
%token UMSTIMMUNG
%token HARMONIE
%token LOGIK
%token FORM
%token INSTRUMENT
%token TASTE
%token MIDI_IN
%token MIDI_OUT
%token ANSONSTEN

%type <integer> bezugs_taste
%type <f_value> GLEITKOMMA_ZAHL

/*  %left '+' '-'  */

%% /* Grammar rules and actions */

start : /* empty */
        | start intervalldeklaration
        | start tondeklaration
        | start tonsystemdeklaration
      	| start umstimmungdeklaration
        | start harmoniedeklaration
        | start logikdeklaration
        | start instrumentdeklaration
        | start error { fatal_error(1,@$.first_line+1); }
      ;

intervalldeklaration :
        INTERVALL intervalldekl1 ;

intervalldekl1 :
          /* empty */
        | intervalldekl1 intervalldekl2_1
      ;

intervalldekl2_1:
          { init_komplex_ton_list (); } intervalldekl2
      ;

intervalldekl2 :
          IDENTIFIER '=' GLEITKOMMA_ZAHL ':' GLEITKOMMA_ZAHL
                    { if ( fabs($5) > 0.001 )
                         get_new_intervall ($1, $3 / $5);
                      else
                         fatal_error (46, $1 ); }

        | IDENTIFIER '=' GLEITKOMMA_ZAHL WURZEL GLEITKOMMA_ZAHL
                    { if ( fabs ($3) > 0.001 )
                          get_new_intervall ($1, pow ($5, 1 / $3));
                      else
                         fatal_error (46, $1); }
/*****
        | IDENTIFIER '=' GLEITKOMMA_ZAHL
                    { get_new_intervall ($1, $3); }
****/
	| IDENTIFIER '=' KOMPLEX_TON_LIST
			 { get_new_intervall_komplex ($1); }
	| IDENTIFIER '=' error { fatal_error(71,$1); }
        | IDENTIFIER error { fatal_error(70,"'='",FEHLERZEILE); }
      ;

tondeklaration :
        TON tondekl1 ;

tondekl1 :
          /* empty */
	| tondekl1 tondekl2_1
      ;

tondekl2_1:
	  { init_komplex_ton_list (); }  tondekl2
      ;

tondekl2 :
          IDENTIFIER '=' GLEITKOMMA_ZAHL
                   { get_new_ton_absolut ($1, $3); }

	| IDENTIFIER '='
		IDENTIFIER '-' KOMPLEX_TON_LIST
		   { get_new_ton_komplex_negative ($1, $3); }

	| IDENTIFIER '='
		     IDENTIFIER
		   { get_new_ton_komplex_positive ($1, $3); }

	| IDENTIFIER '='
		     IDENTIFIER '+' KOMPLEX_TON_LIST
		   { get_new_ton_komplex_positive ($1, $3); }

        | IDENTIFIER '=' error { fatal_error( 72, $1 ); }
      ;

KOMPLEX_TON_LIST:
	  KOMPLEX_TON_START KOMPLEX_TON_LIST_2
	;


KOMPLEX_TON_LIST_2 :
	  /* empty */
	| KOMPLEX_TON_LIST_2 KOMPLEX_TON_1

KOMPLEX_TON_1 :
          '+' IDENTIFIER
                   { get_new_faktor_anteil ( (double) 1, $2); }

        | '-' IDENTIFIER
                   { get_new_faktor_anteil ( (double) -1, $2); }

        | '+' GLEITKOMMA_ZAHL IDENTIFIER
                   { get_new_faktor_anteil ( $2, $3); }

        | '-' GLEITKOMMA_ZAHL IDENTIFIER
                   { get_new_faktor_anteil ( -($2), $3); }

        | '+' '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '-' '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '+' GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($4) > 0.001 )
                       get_new_faktor_anteil ( ($2) / ($4), $5);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '-' GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($4) > 0.001 )
                       get_new_faktor_anteil ( -($2) / ($4), $5);
                     else
                       fatal_error(53, FEHLERZEILE);  }
/******
        | '+'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) 1, $3, $5); }

        | '-'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

        | '+' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( $2, $4, $6); }

        | '-' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
**********/
        ;

KOMPLEX_TON_START :
	  IDENTIFIER
		   { get_new_faktor_anteil ( (double) 1.0 , $1); }

/***
        | '-' IDENTIFIER
                   { get_new_faktor_anteil ( (double) -1.0 , $2); }
***/

	|  GLEITKOMMA_ZAHL IDENTIFIER
		   { get_new_faktor_anteil ( $1, $2); }

        |  '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($2) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ($2), $3);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( ($1) / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }
/****
        | '-' GLEITKOMMA_ZAHL IDENTIFIER
                   { get_new_faktor_anteil ( -($2), $3); }
****/

/********
	|  '(' IDENTIFIER ',' IDENTIFIER ')'
	    { get_new_relativ_anteil ( (double) 1, $2, $4); }

        | '-'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

	|  GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
	    { get_new_relativ_anteil ( $1, $3, $5); }

        | '-' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
**********/
        ;

tonsystemdeklaration :
        TONSYSTEM tonsystemdekl1 ;

tonsystemdekl1 :
          /* empty */
        | tonsystemdekl1 tonsystemdekl2_1
      ;
      
tonsystemdekl2_1:
         { init_ton_liste (); } tonsystemdekl2
      ;

tonsystemdekl2 : 
         IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                        KOMPLEX_TON_LIST
                   { get_new_tonsystem ($1, $3); }
      |  IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                    '-' KOMPLEX_TON_LIST
                   { get_new_tonsystem_negative ($1, $3); }
      ;

tonliste : ton_element | tonliste ',' ton_element ;

ton_element :
          IDENTIFIER      { get_new_ton_in_tonsystem ($1); }
        | /* empty */     { get_new_ton_in_tonsystem (NULL); }
        | error { fatal_error(73,FEHLERZEILE); }
      ;

parameter_liste :      /* allgemein eine Liste von Identifiern */
          IDENTIFIER      { get_new_name_in_parameterlist ($1); }
        | parameter_liste ',' IDENTIFIER
                          { get_new_name_in_parameterlist ($3); }
        | error { fatal_error(74,FEHLERZEILE); }
        ;


argument_liste :
        argument_listenelement {}
        | argument_liste ',' argument_listenelement {}
        | error { fatal_error(74,FEHLERZEILE); }
        ;

argument_listenelement :        /* allgemein eine Liste von Identifiern
                          oder Kommazahlen */
          IDENTIFIER      { get_new_name_in_argument_list ($1);   }
        | INTEGER        { get_new_number_in_argument_list ($1); }
        | '-' INTEGER        { get_new_number_in_argument_list (-($2)); }

        ;


umstimmungdeklaration :
        UMSTIMMUNG umstimmungs_dekl_1 ;

umstimmungs_dekl_1 :
          /* empty */
        | umstimmungs_dekl_1 umstimmungs_dekl_2
      ;

umstimmungs_dekl_2 :
          IDENTIFIER
                    { init_umstimmung ($1);
                      init_parameter_liste (); }
          '='       { eintrage_parameterliste_in_umstimmung (); }
          umstimmungs_dekl_3
                    { get_new_umstimmung (); }
        |
          IDENTIFIER
                    { init_umstimmung ($1);
                      init_parameter_liste (); }
          '(' parameter_liste ')' '=' 
                    { eintrage_parameterliste_in_umstimmung (); }
          umstimmungs_dekl_3 
                    { get_new_umstimmung (); }
        ;
        
umstimmungs_dekl_3 :
          umstimmungs_dekl_taste_abs            {}
        | umstimmungs_dekl_taste_rel            {}
        | umstimmungs_dekl_breite_abs           {}
        | umstimmungs_dekl_breite_rel           {}
        | umstimmungs_dekl_tonhoehe_veraendert  {}
        | umstimmungs_dekl_wiederholung_abs     {}
        | umstimmungs_dekl_wiederholung_rel     {}
        | umstimmungs_dekl_umstimmungs_bund     {}
        | umstimmungs_dekl_umstimmungs_case     {} 
        | umstimmungs_dekl_midi_out             {}  
        | error {fatal_error(75,FEHLERZEILE);}   
        ;


umstimmungs_dekl_taste_abs :
          INTEGER '[' ']'
          { get_umstimmung_taste_abs (zahl, $1, NULL); }
        | IDENTIFIER '[' ']'
          { get_umstimmung_taste_abs (parameter, 0.0, $1); }
        ;

umstimmungs_dekl_taste_rel :
          '@' '+' INTEGER '[' ']'
          { get_umstimmung_taste_rel (zahl, $3, NULL, '+'); }
        | '@' '+' IDENTIFIER '[' ']'
          { get_umstimmung_taste_rel (parameter, 0.0, $3, '+'); }
        | '@' '-' INTEGER '[' ']'
          { get_umstimmung_taste_rel (zahl, $3, NULL, '-'); }
        | '@' '-' IDENTIFIER '[' ']'
          { get_umstimmung_taste_rel (parameter, 0.0, $3, '-'); }
        ;

umstimmungs_dekl_breite_abs :
          '[' '<' '<' INTEGER '>' '>' ']'
          { get_umstimmung_breite_abs (zahl, $4, NULL); }
        | '[' '<' '<' IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_abs (parameter, 0.0, $4); }
        ;

umstimmungs_dekl_breite_rel :
          '[' '<' '<' '@' '+' INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '+'); }
        | '[' '<' '<' '@' '+' IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '+'); }
        | '[' '<' '<' '@' '-' INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '-'); }
        | '[' '<' '<' '@' '-' IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '-'); }
        | '[' '<' '<' '@' '*' INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '*'); }
        | '[' '<' '<' '@' '*' IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '*'); }
        | '[' '<' '<' '@' '/' INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '/'); }
        | '[' '<' '<' '@' '/' IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '/'); }
        ;

umstimmungs_dekl_tonhoehe_veraendert :
          '[' 
            { init_umstimm_expression_list (); }
          nonempty_umstimm_expression_list ']'
          { get_umstimmung_tonhoehe_veraendert (); }
        ;

/* Eine leere Liste von Umstimm-expression kollidiert syntaktisch
   mit "umstimmungs-wiederholung" oder "umstimmungs-bund" */
        
nonempty_umstimm_expression_list :
          nonempty_umstimm_expression {}
        | nonempty_umstimm_expression ',' umstimm_expression_list {}

        | ','      { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   } 
          umstimm_expression_list {}
        ;
        
umstimm_expression_list :
          umstimm_expression {}
        | umstimm_expression_list ',' umstimm_expression {}
        ;
        
umstimm_expression :
          /* empty */
                   { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
        | 
          nonempty_umstimm_expression
        ;
        
nonempty_umstimm_expression :
          IDENTIFIER  { get_new_umstimm_expression ($1); }
        | '@'         { get_new_umstimm_expression ("@"); }

        | IDENTIFIER '+' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_positive ($1); }
        | '@' '+' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_positive ( "@" ); }
        | IDENTIFIER '-' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_negative ($1); }
        | '@' '-' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_negative ( "@" ); }
        ;
        
        
umstimmungs_dekl_wiederholung_abs :
          '[' ']' { init_komplex_ton_list (); }
                      KOMPLEX_TON_LIST
          { get_umstimmung_wiederholung_abs (); }
        | '[' ']' { init_komplex_ton_list (); }
                 '-'  KOMPLEX_TON_LIST
          { get_umstimmung_wiederholung_abs_negative (); }
        ;

umstimmungs_dekl_wiederholung_rel :
          '[' ']' '@' '+' { init_komplex_ton_list (); }
                            KOMPLEX_TON_LIST
          { get_umstimmung_wiederholung_rel_positive (); }
        | '[' ']' '@' '-' { init_komplex_ton_list (); }
                            KOMPLEX_TON_LIST
          { get_umstimmung_wiederholung_rel_negative (); }
        ;

umstimmungs_dekl_umstimmungs_bund :
          '{' { init_aktions_liste (); } 
          aktions_liste '}'
          { get_umstimmung_umstimmungs_bund (); }
        ;
        
aktions_liste :
          aktion {}
        | aktions_liste ',' aktion {}
        ;
        
aktion : 
          IDENTIFIER { init_argument_liste (); 
                       get_new_aktion_aufruf_element ($1); }
        | IDENTIFIER '(' { init_argument_liste (); }
            argument_liste ')'
          { get_new_aktion_aufruf_element ($1); }
        | MIDI_OUT '(' 
		              { init_integersequenz ();}
		           integersequenz ')' 
		  { get_new_aktion_midi_out_element (); }
        ;          

umstimmungs_dekl_umstimmungs_case :
          INTEGER '{' { init_umstimmungs_case_liste (); } 
          umstimmungs_case_liste '}'
          { get_umstimmung_umstimm_case_zahl ($1); }
        | IDENTIFIER '{' { init_umstimmungs_case_liste (); } 
          umstimmungs_case_liste '}'
          { get_umstimmung_umstimm_case_parameter ($1); }
        ;

umstimmungs_case_liste :
          umstimmungs_case_element {}
        | umstimmungs_case_liste  umstimmungs_case_element {}
        ;

umstimmungs_case_element :
          INTEGER '-' '>' 
             { init_aktions_liste (); }
             aktions_liste 
             { get_umstimmungs_case_zahl_element ($1); }
        | '-' INTEGER '-' '>' 
             { init_aktions_liste (); }
             aktions_liste 
             { get_umstimmungs_case_zahl_element (-($2)); }
        | ANSONSTEN '-' '>' 
             { init_aktions_liste (); }
             aktions_liste
             { get_umstimmungs_case_default_element (); }
        ;

umstimmungs_dekl_midi_out:  
		  MIDI_OUT '(' 
		              { init_integersequenz ();}
		           integersequenz ')' 
		              { get_umstimmung_midi_out (); }

        

harmoniedeklaration :
          HARMONIE harmonie_dekl_1 {}
        ;
        
harmonie_dekl_1 :
          /* empty */ {}
        | harmonie_dekl_1  harmonie_dekl_2 {}
        ;
        
harmonie_dekl_2 :
          IDENTIFIER '=' '{' 
            { init_tastenliste (); }
          tasten_liste '}' bezugs_taste
            { get_new_harmonie ($1, $7); }

         | IDENTIFIER '=' error { fatal_error(76,$1); }
        ;
        
bezugs_taste :
          /* empty */      { $$ = -1; }
        | '.' INTEGER     { $$ = $2; }
        ;
        
tasten_liste :
          taste {}
        | tasten_liste ',' taste {}
        ;

taste :
          INTEGER      { get_new_taste ( $1, '+'); }
        | '*' INTEGER  { get_new_taste ( $2, '*'); }
        ;
        
logikdeklaration :
          LOGIK logik_dekl_1 {}
        ;
        
logik_dekl_1 :
          /* empty */ {}
        | logik_dekl_1 { init_ausloeser ();
                         /* fÅr die Anfangsausloesung der Logik */
                       } 
               logik_dekl_2 {}
        ;
        
logik_dekl_2 :
          IDENTIFIER ausloeser '=' '[' 
              { get_new_logik ($1, NULL);
                init_anweisungs_liste (); }
          anweisungs_liste ']'
              { vervollstaendige_logik (); }
        | IDENTIFIER ausloeser '=' IDENTIFIER '[' 
              { get_new_logik ($1, $4);
                init_anweisungs_liste (); }
          anweisungs_liste ']'
              { vervollstaendige_logik (); }
        ;
        
anweisungs_liste :
          /* empty */ {}
        | anweisungs_liste anweisung {}
        ;


anweisung :
          ausloeser '-' '>' '{' { init_aktions_liste (); } 
                               aktions_liste '}'
                       { get_new_anweisung (); }
        |
          ausloeser '-' '>'     { init_aktions_liste (); } 
                               aktion 
                       { get_new_anweisung (); }
        ;
        
harmoniebezeichner :
          INTEGER '~' IDENTIFIER '~' INTEGER
              { get_harmoniebezeichner (  $1, $3,  $5); }
        |              IDENTIFIER '~' INTEGER
              { get_harmoniebezeichner (-1, $1,  $3); }
        | INTEGER '~' IDENTIFIER
              { get_harmoniebezeichner (  $1, $3, -1); }
        |              IDENTIFIER 
              { get_harmoniebezeichner (-1, $1, -1); }
        ; 
 
ausloeser :
          ANSONSTEN { get_ausloeser_default (); }
        | harmoniebezeichner  { get_ausloeser_harmonie (); }
        | FORM harmoniebezeichner { get_ausloeser_harmonie_form (); }
        | TASTE IDENTIFIER { get_ausloeser_taste ($2); fprintf(stderr,"Taste akzeptiert"); }
        | MIDI_IN '(' { init_integersequenz (); }
              integersequenz ')' 
                      { get_ausloeser_midi_in (); }
        ;
        
integersequenz :
          INTEGER 
              { get_new_integer_in_integersequenz ($1);}
        | integersequenz ',' INTEGER 
              { get_new_integer_in_integersequenz ($3);}
        | error { fatal_error( 77, FEHLERZEILE ); }
        ;
 

instrumentdeklaration :
          INSTRUMENT instrument_dekl_1 {}
        ;
        
instrument_dekl_1 :
          /* empty */ {}
        | instrument_dekl_1 instrument_dekl_2 {}
        ;

instrument_dekl_2 :
          INTEGER '-' '>' INTEGER 
             { get_instrument_dekl ($1, $4, $4, 0, & list_of_instrumente); }
        | INTEGER '-' '>' INTEGER '-' INTEGER 
             { get_instrument_dekl ($1, $4, $6, 0, & list_of_instrumente); }
        | INTEGER '-' '>' '[' INTEGER ']' 
             { get_instrument_dekl ($1, 0, 0, $5, & list_of_instrumente); }
        | INTEGER '-' '>' INTEGER '[' INTEGER ']'
             { get_instrument_dekl ($1, $4, $4, $6, & list_of_instrumente); }
        | INTEGER '-' '>' INTEGER '-' INTEGER '[' INTEGER ']'
             { get_instrument_dekl ($1, $4, $6, $8, & list_of_instrumente); }
        ;
        
GLEITKOMMA_ZAHL:
           F_NUMBER  { $$ = $1; }
        |  INTEGER   { $$ = (double) $1; }
        ;

        
%%

	/* anderen Lexer verwenden */
#undef yylex
#undef init_yylex
int yylex(void) 
{
  YYLTYPE yylloc;
  YYSTYPE yylval;
  int c;
  
 start_lex:
  
#ifdef DEBUG
  if (mutabor_debug_level)
    printf("Leerkram ignorieren\n");
#endif

  /* Ignore whitespace, get first nonwhitespace character */
  while ( anzahl_eingelesene_zeichen ++,
	  (c = toupper( intern_fgetc(mutabor_parser_in) )) == ' ' 
          || c == '\t'
          || c == '\n'
	  || c == '\r') {
    
    if (c == '\n') 
#ifdef ACS_VERSION
      if (!(yylloc.first_line ++ % LINE_DRAW_QUANTUM)) 
	show_line_number(yylloc.first_line);
#else
    yylloc.first_line ++;
#endif
  }

#ifdef DEBUG
  if (mutabor_debug_level)
    printf("Token start: '%c'\n",c);
#endif

  
  if (c == '"') {
#ifdef DEBUG
    if (mutabor_debug_level)
      printf("Kommentar:\n");
#endif

    while (anzahl_eingelesene_zeichen ++,
	   (c=intern_fgetc(mutabor_parser_in)) != '"' && c != EOF ){
      if (c == '\n') yylloc.first_line ++;
#ifdef DEBUG
      if (mutabor_debug_level)
	printf("%c",c);
#endif
    }
#ifdef DEBUG
    if (mutabor_debug_level)
      printf("Kommentar Ende.\n");
#endif
    goto start_lex;
  }

  if (c == EOF) {
#ifdef DEBUG
    if (mutabor_debug_level)
      printf("Dateiende.\n");
#endif
    return 0;
  }
  
  /* char starts a number => parse the number. */
  if (isdigit(c)) {
#ifdef DEBUG
    if (mutabor_debug_level)
      printf("Zahl.\n");
#endif
    
#if 1
    double zahl = 0.0;
    while (isdigit(c)) {
      zahl *= 10;
      zahl += ( c - '0' );
      anzahl_eingelesene_zeichen ++;
      c = intern_fgetc (mutabor_parser_in);
    }
    if (c == '.') {    /* dann nachkommastellen */
      double faktor = 1.0;
      while (anzahl_eingelesene_zeichen ++,
	     isdigit (c = intern_fgetc (mutabor_parser_in))) {
	faktor /= 10;
	zahl += faktor * ( c - '0' );
      }
      intern_ungetc (c, mutabor_parser_in);
      anzahl_eingelesene_zeichen --;
      yylval.f_value = zahl;
      return F_NUMBER;
    }
    else {
      intern_ungetc (c, mutabor_parser_in);
      anzahl_eingelesene_zeichen --;
      
      if (zahl > INT_MAX) {
	yylval.f_value = zahl;
	return F_NUMBER;
      }
      else {
	yylval.integer = (int)zahl;
	return INTEGER;
      }
    }
#else

    intern_ungetc (c, mutabor_parser_in);
    anzahl_eingelesene_zeichen --;
    fscanf (mutabor_parser_in, "%lf", &yylval.f_value);
    
#endif
    
    /*
      printf("f_number:%lf:\n", yylval.f_value); 
    */
    
  }
  
  /* # starts a HEX-number => parse the number. */
  if (c == '#') {
    int help;
    if (fscanf (mutabor_parser_in, "%x", &help) == 0) {
      fatal_error (78, yylloc.first_line + 1);
      exit (1);
    }
    yylval.integer = help;
    
    /* printf("f_number:%lf:\n", yylval.f_value); */
    
    return INTEGER;
  }
  
  /* Test auf reserved word oder einen Identifier */
  if (isalpha (c) || (c == '_') || (c == '\'') ) {
    
    static struct { 
      char *word;
      int token;
    } reserved_words [] = {
      /* Deutsche SchlÅsselworte : */
      { "INTERVALL"  , INTERVALL  },
      { "WURZEL"     , WURZEL     },
      { "TON"        , TON        },
      { "TONSYSTEM"  , TONSYSTEM  },
      { "UMSTIMMUNG" , UMSTIMMUNG },
      { "HARMONIE"   , HARMONIE   },
      { "LOGIK"      , LOGIK      },
      { "FORM"       , FORM       },
      { "MIDIKANAL" , INSTRUMENT },
      { "TASTE"      , TASTE      },
      { "MIDIIN"     , MIDI_IN    },
      { "MIDIOUT"    , MIDI_OUT   },
      { "ANSONSTEN"  , ANSONSTEN  },
      /* Englische SchlÅsselworte : */
      { "INTERVAL"  , INTERVALL  },
      { "ROOT"     , WURZEL     },
      { "TONE"        , TON        },
      { "TONESYSTEM"  , TONSYSTEM  },
      { "RETUNING" , UMSTIMMUNG },
      { "PATTERN"   , HARMONIE   },
      { "LOGIC"      , LOGIK      },
      { "SHIFTED"       , FORM       },
      { "MIDICHANNEL" , INSTRUMENT },
      { "KEY"      , TASTE      },
      { "ELSE"  , ANSONSTEN  },
      { NULL         , 0          }
    };
    

#if 0
    char *symbuffer = xmalloc ((size_t)(MAX_IDENTIFIER_LEN + 1));
    int i=0;
    
    do {
      if (c == '\'') c = 'i';
      symbuffer[i++] = c;
      c = toupper(intern_fgetc (mutabor_parser_in));
    } while (c != EOF                && 
	     i < MAX_IDENTIFIER_LEN  && 
	     (isalnum (c) || (c == '_') || (c == '\'') ) );
    
    intern_ungetc (c, mutabor_parser_in);
    symbuffer[i] = '\0';
#else
    int i = 0;
    int max_identifier_len = 10;
    char *symbuffer = (char*) xmalloc ((size_t) max_identifier_len);
    
    do {
      if (c == '\'') c = 'i';
      
      if ( i + 1 == max_identifier_len ) {
	char * help = (char*) xrealloc (symbuffer, (size_t) (max_identifier_len += 10));
	memmove (help, symbuffer, (size_t) max_identifier_len);
	symbuffer = help;
      }
      
      symbuffer[i++] = c;
      c = toupper(intern_fgetc (mutabor_parser_in));
      anzahl_eingelesene_zeichen ++;
      
    } while (c != EOF                && 
	     (isalnum (c) || (c == '_') || (c == '\'') ) );
    
    intern_ungetc (c, mutabor_parser_in);
    anzahl_eingelesene_zeichen --;
    symbuffer[i] = '\0';
	
#endif
    
    /* printf("symbuffer:%s:\n", symbuffer); */
    
    for (i=0; reserved_words[i].word; i++) {
      if ( ! strcmp (symbuffer, reserved_words[i].word)) {
	xfree (symbuffer);
	return reserved_words[i].token;
      }
    }
    
    yylval.identifier = symbuffer;
    return IDENTIFIER;
  }
  
  /* Any other character is a token by itself */
  switch (c) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '[':
  case ']':
  case ':':
  case '=':
  case '(':
  case ')':
  case ',':
  case '~':
  case '@':
  case '<':
  case '>':
  case '{':
  case '}':
  case ';':
    return c;
  }

  fprintf(stderr,"Lexer: durchgefallen");
  fatal_error(2,c,yylloc.first_line + 1);
  
  return 0;  /* um Compilerwarnungen zu vermeiden */
  
  
} /* yylex */

void init_yylex (void)
{
  YYLTYPE yylloc;
  yylloc.first_line = 0;
  anzahl_eingelesene_zeichen = 0;
}

void yyerror(char *s) {
  fprintf(stderr,s);
  /*
  return 1;
  */
/* ignore it ! */
  
} /* yyerror */



/* END MUT_TAB.C */
