/** \file                             -*- C -*- 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/mut.y,v 1.11 2011/09/06 08:09:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/06 08:09:21 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
/* Mutabor Tonsysteme */
%locations

%{

/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

//#pragma warn -cln
//#pragma warn -aus
//#pragma warn -sig
//#pragma warn -par


#include <ctype.h>
#include <limits.h>
#include "src/kernel/Global.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/Hilfs.h"

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line+1

#ifdef alloca
#undef alloca
#define alloca make_an_error ---
#endif
#define YYMALLOC xmalloc
#define YYFREE(X) do { /* empty */; } while (YYID (0))
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */

%}

%union {
    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */
}

%token <identifier> MUTABOR_TOKEN_IDENTIFIER
%token <f_value> MUTABOR_TOKEN_F_NUMBER
%token <integer> MUTABOR_TOKEN_INTEGER

%token MUTABOR_TOKEN_INTERVAL
%token MUTABOR_TOKEN_ROOT
%token MUTABOR_TOKEN_TONE
%token MUTABOR_TOKEN_TONESYSTEM
%token MUTABOR_TOKEN_RETUNING
%token MUTABOR_TOKEN_HARMONY
%token MUTABOR_TOKEN_LOGIC
%token MUTABOR_TOKEN_FORM
%token MUTABOR_TOKEN_MIDICHANNEL
%token MUTABOR_TOKEN_KEY
%token MUTABOR_TOKEN_MIDI_IN
%token MUTABOR_TOKEN_MIDI_OUT
%token MUTABOR_TOKEN_ELSE
%token MUTABOR_TOKEN_SPACES
%token MUTABOR_TOKEN_COMMENT
%token MUTABOR_TOKEN_COMMENT_START
%token MUTABOR_TOKEN_COMMENT_END
%token MUTABOR_TOKEN_PARAMETER
%token MUTABOR_TOKEN_OTHER
%token MUTABOR_TOKEN_CALLS
%token MUTABOR_TOKEN_ERROR
%token MUTABOR_TOKEN_ENDOFFILE

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
        | start error {  fatal_error(1,FEHLERZEILE); }
      ;

intervalldeklaration :
        MUTABOR_TOKEN_INTERVAL intervalldekl1 ;

intervalldekl1 :
          /* empty */
        | intervalldekl1 intervalldekl2_1
      ;

intervalldekl2_1:
          { init_komplex_ton_list (); } intervalldekl2
      ;

intervalldekl2 :
          MUTABOR_TOKEN_IDENTIFIER '=' GLEITKOMMA_ZAHL ':' GLEITKOMMA_ZAHL
                    { if ( fabs($5) > 0.001 )
                         get_new_intervall ($1, $3 / $5);
                      else
			fatal_error (46, mutC_STR($1) ); }

        | MUTABOR_TOKEN_IDENTIFIER '=' GLEITKOMMA_ZAHL MUTABOR_TOKEN_ROOT GLEITKOMMA_ZAHL
                    { if ( fabs ($3) > 0.001 )
                          get_new_intervall ($1, pow ($5, 1 / $3));
                      else
			fatal_error (46, mutC_STR($1)); }
/*****
        | MUTABOR_TOKEN_IDENTIFIER '=' GLEITKOMMA_ZAHL
                    { get_new_intervall ($1, $3); }
****/
	| MUTABOR_TOKEN_IDENTIFIER '=' KOMPLEX_TON_LIST
			 { get_new_intervall_komplex ($1); }
        | MUTABOR_TOKEN_IDENTIFIER '=' error { fatal_error(71, mutC_STR($1)); }
        | MUTABOR_TOKEN_IDENTIFIER error { fatal_error(70,mutT("="),FEHLERZEILE); }
      ;

tondeklaration :
        MUTABOR_TOKEN_TONE tondekl1 ;

tondekl1 :
          /* empty */
	| tondekl1 tondekl2_1
      ;

tondekl2_1:
	  { init_komplex_ton_list (); }  tondekl2
      ;

tondekl2 :
          MUTABOR_TOKEN_IDENTIFIER '=' GLEITKOMMA_ZAHL
                   { get_new_ton_absolut ($1, $3); }

	| MUTABOR_TOKEN_IDENTIFIER '='
		MUTABOR_TOKEN_IDENTIFIER '-' KOMPLEX_TON_LIST
		   { get_new_ton_komplex_negative ($1, $3); }

	| MUTABOR_TOKEN_IDENTIFIER '='
		     MUTABOR_TOKEN_IDENTIFIER
		   { get_new_ton_komplex_positive ($1, $3); }

	| MUTABOR_TOKEN_IDENTIFIER '='
		     MUTABOR_TOKEN_IDENTIFIER '+' KOMPLEX_TON_LIST
		   { get_new_ton_komplex_positive ($1, $3); }

      | MUTABOR_TOKEN_IDENTIFIER '=' error { fatal_error( 72, mutC_STR($1) ); }
      ;

KOMPLEX_TON_LIST:
	  KOMPLEX_TON_START KOMPLEX_TON_LIST_2
	;


KOMPLEX_TON_LIST_2 :
	  /* empty */
	| KOMPLEX_TON_LIST_2 KOMPLEX_TON_1

KOMPLEX_TON_1 :
          '+' MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( (double) 1, $2); }

        | '-' MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( (double) -1, $2); }

        | '+' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( $2, $3); }

        | '-' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( -($2), $3); }

        | '+' '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '-' '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '+' GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($4) > 0.001 )
                       get_new_faktor_anteil ( ($2) / ($4), $5);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | '-' GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($4) > 0.001 )
                       get_new_faktor_anteil ( -($2) / ($4), $5);
                     else
                       fatal_error(53, FEHLERZEILE);  }
/******
        | '+'  '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) 1, $3, $5); }

        | '-'  '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

        | '+' GLEITKOMMA_ZAHL '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( $2, $4, $6); }

        | '-' GLEITKOMMA_ZAHL '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
**********/
        ;

KOMPLEX_TON_START :
	  MUTABOR_TOKEN_IDENTIFIER
		   { get_new_faktor_anteil ( (double) 1.0 , $1); }

/***
        | '-' MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( (double) -1.0 , $2); }
***/

	|  GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
		   { get_new_faktor_anteil ( $1, $2); }

        |  '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($2) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ($2), $3);
                     else
                       fatal_error(53, FEHLERZEILE);  }

        | GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { if ( fabs($3) > 0.001 )
                       get_new_faktor_anteil ( ($1) / ($3), $4);
                     else
                       fatal_error(53, FEHLERZEILE);  }
/****
        | '-' GLEITKOMMA_ZAHL MUTABOR_TOKEN_IDENTIFIER
                   { get_new_faktor_anteil ( -($2), $3); }
****/

/********
	|  '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
	    { get_new_relativ_anteil ( (double) 1, $2, $4); }

        | '-'  '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

	|  GLEITKOMMA_ZAHL '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
	    { get_new_relativ_anteil ( $1, $3, $5); }

        | '-' GLEITKOMMA_ZAHL '(' MUTABOR_TOKEN_IDENTIFIER ',' MUTABOR_TOKEN_IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
**********/
        ;

tonsystemdeklaration :
        MUTABOR_TOKEN_TONESYSTEM tonsystemdekl1 ;

tonsystemdekl1 :
          /* empty */
        | tonsystemdekl1 tonsystemdekl2_1
      ;
      
tonsystemdekl2_1:
         { init_ton_liste (); } tonsystemdekl2
      ;

tonsystemdekl2 : 
         MUTABOR_TOKEN_IDENTIFIER '=' MUTABOR_TOKEN_INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                        KOMPLEX_TON_LIST
                   { get_new_tonsystem ($1, $3); }
      |  MUTABOR_TOKEN_IDENTIFIER '=' MUTABOR_TOKEN_INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                    '-' KOMPLEX_TON_LIST
                   { get_new_tonsystem_negative ($1, $3); }
      ;

tonliste : ton_element | tonliste ',' ton_element ;

ton_element :
          MUTABOR_TOKEN_IDENTIFIER      { get_new_ton_in_tonsystem ($1); }
        | /* empty */     { get_new_ton_in_tonsystem (NULL); }
        | error { fatal_error(73,FEHLERZEILE); }
      ;

parameter_liste :      /* allgemein eine Liste von Identifiern */
MUTABOR_TOKEN_IDENTIFIER      { get_new_name_in_parameterlist ($1); }
        | parameter_liste ',' MUTABOR_TOKEN_IDENTIFIER
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
MUTABOR_TOKEN_IDENTIFIER      { get_new_name_in_argument_list ($1) ;  }
| MUTABOR_TOKEN_INTEGER        { get_new_number_in_argument_list ($1) ;  }
| '-' MUTABOR_TOKEN_INTEGER        { get_new_number_in_argument_list (-($2)); }

        ;


umstimmungdeklaration :
        MUTABOR_TOKEN_RETUNING umstimmungs_dekl_1 ;

umstimmungs_dekl_1 :
          /* empty */
        | umstimmungs_dekl_1 umstimmungs_dekl_2
      ;

umstimmungs_dekl_2 :
          MUTABOR_TOKEN_IDENTIFIER
                    { init_umstimmung ($1);
                      init_parameter_liste (); }
          '='       { eintrage_parameterliste_in_umstimmung (); }
          umstimmungs_dekl_3
                    { get_new_umstimmung (); }
        |
          MUTABOR_TOKEN_IDENTIFIER
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
          MUTABOR_TOKEN_INTEGER '[' ']'
          { get_umstimmung_taste_abs (zahl, $1, NULL); }
        | MUTABOR_TOKEN_IDENTIFIER '[' ']'
          { get_umstimmung_taste_abs (parameter, 0.0, $1); }
        ;

umstimmungs_dekl_taste_rel :
          '@' '+' MUTABOR_TOKEN_INTEGER '[' ']'
          { get_umstimmung_taste_rel (zahl, $3, NULL, '+'); }
        | '@' '+' MUTABOR_TOKEN_IDENTIFIER '[' ']'
          { get_umstimmung_taste_rel (parameter, 0.0, $3, '+'); }
        | '@' '-' MUTABOR_TOKEN_INTEGER '[' ']'
          { get_umstimmung_taste_rel (zahl, $3, NULL, '-'); }
        | '@' '-' MUTABOR_TOKEN_IDENTIFIER '[' ']'
          { get_umstimmung_taste_rel (parameter, 0.0, $3, '-'); }
        ;

umstimmungs_dekl_breite_abs :
          '[' '<' '<' MUTABOR_TOKEN_INTEGER '>' '>' ']'
          { get_umstimmung_breite_abs (zahl, $4, NULL); }
        | '[' '<' '<' MUTABOR_TOKEN_IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_abs (parameter, 0.0, $4); }
        ;

umstimmungs_dekl_breite_rel :
          '[' '<' '<' '@' '+' MUTABOR_TOKEN_INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '+'); }
        | '[' '<' '<' '@' '+' MUTABOR_TOKEN_IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '+'); }
        | '[' '<' '<' '@' '-' MUTABOR_TOKEN_INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '-'); }
        | '[' '<' '<' '@' '-' MUTABOR_TOKEN_IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '-'); }
        | '[' '<' '<' '@' '*' MUTABOR_TOKEN_INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '*'); }
        | '[' '<' '<' '@' '*' MUTABOR_TOKEN_IDENTIFIER '>' '>' ']'
          { get_umstimmung_breite_rel (parameter, 0.0, $6, '*'); }
        | '[' '<' '<' '@' '/' MUTABOR_TOKEN_INTEGER '>' '>' ']'
          { get_umstimmung_breite_rel (zahl, $6, NULL, '/'); }
        | '[' '<' '<' '@' '/' MUTABOR_TOKEN_IDENTIFIER '>' '>' ']'
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
          MUTABOR_TOKEN_IDENTIFIER  { get_new_umstimm_expression ($1); }
        | '@'         { get_new_umstimm_expression ("@"); }

        | MUTABOR_TOKEN_IDENTIFIER '+' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_positive ($1); }
        | '@' '+' { init_komplex_ton_list (); } 
          KOMPLEX_TON_LIST 
                   { get_new_umstimm_expression_positive ( "@" ); }
        | MUTABOR_TOKEN_IDENTIFIER '-' { init_komplex_ton_list (); } 
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
          MUTABOR_TOKEN_IDENTIFIER { init_argument_liste (); 
                       get_new_aktion_aufruf_element ($1); }
        | MUTABOR_TOKEN_IDENTIFIER '(' { init_argument_liste (); }
            argument_liste ')'
          { get_new_aktion_aufruf_element ($1); }
        | MUTABOR_TOKEN_MIDI_OUT '(' 
		              { init_integersequenz ();}
		           integersequenz ')' 
		  { get_new_aktion_midi_out_element (); }
        ;          

umstimmungs_dekl_umstimmungs_case :
          MUTABOR_TOKEN_INTEGER '{' { init_umstimmungs_case_liste (); } 
          umstimmungs_case_liste '}'
          { get_umstimmung_umstimm_case_zahl ($1); }
        | MUTABOR_TOKEN_IDENTIFIER '{' { init_umstimmungs_case_liste (); } 
          umstimmungs_case_liste '}'
          { get_umstimmung_umstimm_case_parameter ($1); }
        ;

umstimmungs_case_liste :
          umstimmungs_case_element {}
        | umstimmungs_case_liste  umstimmungs_case_element {}
        ;

umstimmungs_case_element :
          MUTABOR_TOKEN_INTEGER '-' '>' 
             { init_aktions_liste (); }
             aktions_liste 
             { get_umstimmungs_case_zahl_element ($1); }
        | '-' MUTABOR_TOKEN_INTEGER '-' '>' 
             { init_aktions_liste (); }
             aktions_liste 
             { get_umstimmungs_case_zahl_element (-($2)); }
        | MUTABOR_TOKEN_ELSE '-' '>' 
             { init_aktions_liste (); }
             aktions_liste
             { get_umstimmungs_case_default_element (); }
        ;

umstimmungs_dekl_midi_out:  
		  MUTABOR_TOKEN_MIDI_OUT '(' 
		              { init_integersequenz ();}
		           integersequenz ')' 
		              { get_umstimmung_midi_out (); }

        

harmoniedeklaration :
          MUTABOR_TOKEN_HARMONY harmonie_dekl_1 {}
        ;
        
harmonie_dekl_1 :
          /* empty */ {}
        | harmonie_dekl_1  harmonie_dekl_2 {}
        ;
        
harmonie_dekl_2 :
          MUTABOR_TOKEN_IDENTIFIER '=' '{' 
            { init_tastenliste (); }
          tasten_liste '}' bezugs_taste
            { get_new_harmonie ($1, $7); }

        | MUTABOR_TOKEN_IDENTIFIER '=' error { fatal_error(76, mutC_STR($1)); }
        ;
        
bezugs_taste :
          /* empty */      { $$ = -1; }
        | '.' MUTABOR_TOKEN_INTEGER     { $$ = $2; }
        ;
        
tasten_liste :
          taste {}
        | tasten_liste ',' taste {}
        ;

taste :
          MUTABOR_TOKEN_INTEGER      { get_new_taste ( $1, '+'); }
        | '*' MUTABOR_TOKEN_INTEGER  { get_new_taste ( $2, '*'); }
        ;
        
logikdeklaration :
          MUTABOR_TOKEN_LOGIC logik_dekl_1 {}
        ;
        
logik_dekl_1 :
          /* empty */ {}
        | logik_dekl_1 { init_ausloeser ();
                         /* fÅr die Anfangsausloesung der Logik */
                       } 
               logik_dekl_2 {}
        ;
        
logik_dekl_2 :
          MUTABOR_TOKEN_IDENTIFIER ausloeser '=' '[' 
              { get_new_logik ($1, NULL);
                init_anweisungs_liste (); }
          anweisungs_liste ']'
              { vervollstaendige_logik (); }
        | MUTABOR_TOKEN_IDENTIFIER ausloeser '=' MUTABOR_TOKEN_IDENTIFIER '[' 
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
          MUTABOR_TOKEN_INTEGER '~' MUTABOR_TOKEN_IDENTIFIER '~' MUTABOR_TOKEN_INTEGER
              { get_harmoniebezeichner (  $1, $3,  $5); }
        |              MUTABOR_TOKEN_IDENTIFIER '~' MUTABOR_TOKEN_INTEGER
              { get_harmoniebezeichner (-1, $1,  $3); }
        | MUTABOR_TOKEN_INTEGER '~' MUTABOR_TOKEN_IDENTIFIER
              { get_harmoniebezeichner (  $1, $3, -1); }
        |              MUTABOR_TOKEN_IDENTIFIER 
              { get_harmoniebezeichner (-1, $1, -1); }
        ; 
 
ausloeser :
          MUTABOR_TOKEN_ELSE { get_ausloeser_default (); }
        | harmoniebezeichner  { get_ausloeser_harmonie (); }
        | MUTABOR_TOKEN_FORM harmoniebezeichner { get_ausloeser_harmonie_form (); }
        | MUTABOR_TOKEN_KEY MUTABOR_TOKEN_IDENTIFIER { get_ausloeser_taste ($2); }
        | MUTABOR_TOKEN_MIDI_IN '(' { init_integersequenz (); }
              integersequenz ')' 
                      { get_ausloeser_midi_in (); }
        ;
        
integersequenz :
          MUTABOR_TOKEN_INTEGER 
              { get_new_integer_in_integersequenz ($1);}
        | integersequenz ',' MUTABOR_TOKEN_INTEGER 
              { get_new_integer_in_integersequenz ($3);}
        | error { fatal_error( 77, FEHLERZEILE ); }
        ;
 

instrumentdeklaration :
          MUTABOR_TOKEN_MIDICHANNEL instrument_dekl_1 {}
        ;
        
instrument_dekl_1 :
          /* empty */ {}
        | instrument_dekl_1 instrument_dekl_2 {}
        ;

instrument_dekl_2 :
          MUTABOR_TOKEN_INTEGER '-' '>' MUTABOR_TOKEN_INTEGER 
             { get_instrument_dekl ($1, $4, $4, 0, & list_of_instrumente); }
        | MUTABOR_TOKEN_INTEGER '-' '>' MUTABOR_TOKEN_INTEGER '-' MUTABOR_TOKEN_INTEGER 
             { get_instrument_dekl ($1, $4, $6, 0, & list_of_instrumente); }
        | MUTABOR_TOKEN_INTEGER '-' '>' '[' MUTABOR_TOKEN_INTEGER ']' 
             { get_instrument_dekl ($1, 0, 0, $5, & list_of_instrumente); }
        | MUTABOR_TOKEN_INTEGER '-' '>' MUTABOR_TOKEN_INTEGER '[' MUTABOR_TOKEN_INTEGER ']'
             { get_instrument_dekl ($1, $4, $4, $6, & list_of_instrumente); }
        | MUTABOR_TOKEN_INTEGER '-' '>' MUTABOR_TOKEN_INTEGER '-' MUTABOR_TOKEN_INTEGER '[' MUTABOR_TOKEN_INTEGER ']'
             { get_instrument_dekl ($1, $4, $6, $8, & list_of_instrumente); }
        ;
        
GLEITKOMMA_ZAHL:
MUTABOR_TOKEN_F_NUMBER  { $$ = $1 ; }
|  MUTABOR_TOKEN_INTEGER   { $$ = (double) $1 ; }
        ;

        
%%
/// \todo check whether this function is necessary for any system but windows
#ifdef __WXMSW__
inline int mutabor_toupper(int c) {
	if (c == EOF) return c;
	else return toupper(c);
}
#ifdef toupper
#undef toupper
#endif
#define toupper mutabor_toupper
#endif

int yylex(void) 
{
    int c;

start_lex:

    /* Ignore whitespace, get first nonwhitespace character */
    while ( anzahl_eingelesene_zeichen ++,

            isspace(c = toupper( intern_fgetc(quelldatei) ))) {
	DEBUGLOG2(other,_T("char %x"),c);

      if (c == '\n') {
	DEBUGLOG2(other,_T("New line"));
	if (!(yylloc.first_line ++ % LINE_DRAW_QUANTUM)) 
	  show_line_number(yylloc.first_line);
      }
    }
    
    if (c == '"') {
       while (anzahl_eingelesene_zeichen ++,
       
              (c=intern_fgetc(quelldatei)) != '"' && c != EOF )
                    if (c == '\n') yylloc.first_line ++;
        
       goto start_lex;
    }

    if (c == EOF) {
      show_line_number(yylloc.first_line);
        return 0;
    }

        
    /* char starts a number => parse the number. */
    if (isdigit(c)) {

#if 1
        double zahl = 0.0;
        while (isdigit(c)) {
            zahl *= 10;
            zahl += ( c - '0' );
            anzahl_eingelesene_zeichen ++;
            c = intern_fgetc (quelldatei);
        }
        if (c == '.') {    /* dann nachkommastellen */
            double faktor = 1.0;
            while (anzahl_eingelesene_zeichen ++,
                   isdigit (c = intern_fgetc (quelldatei))) {
                faktor /= 10;
                zahl += faktor * ( c - '0' );
            }
            intern_ungetc (c, quelldatei);
            anzahl_eingelesene_zeichen --;
            yylval.f_value = zahl;
            return MUTABOR_TOKEN_F_NUMBER;
        }
        else {
            intern_ungetc (c, quelldatei);
            anzahl_eingelesene_zeichen --;
            
            if (zahl > INT_MAX) {
                yylval.f_value = zahl;
                return MUTABOR_TOKEN_F_NUMBER;
            }
            else {
                yylval.integer = (int)zahl;
                return MUTABOR_TOKEN_INTEGER;
            }
        }
#else

        intern_ungetc (c, quelldatei);
        anzahl_eingelesene_zeichen --;
        fscanf (quelldatei, "%lf", &yylval.f_value);

#endif

/*
 printf("f_number:%lf:\n", yylval.f_value); 
*/
      
    }
    
    /* # starts a HEX-number => parse the number. */
    if (c == '#') {
        unsigned int help;
        if (fscanf (quelldatei, "%x", &help) == 0) {
            fatal_error (78, yylloc.first_line + 1);
            exit (1);
        }
        yylval.integer = help;

/* printf("f_number:%lf:\n", yylval.f_value); */

        return MUTABOR_TOKEN_INTEGER;
    }
    
    /* Test auf reserved word oder einen Identifier */
    if (isalpha (c) || (c == '_') || (c == '\'') ) {

static struct { 
    const char *word;
    int token;
} reserved_words [] = {
/* German keywords : */
{ "INTERVALL"  , MUTABOR_TOKEN_INTERVAL  },
{ "WURZEL"     , MUTABOR_TOKEN_ROOT     },
{ "TON"        , MUTABOR_TOKEN_TONE        },
{ "TONSYSTEM"  , MUTABOR_TOKEN_TONESYSTEM  },
{ "UMSTIMMUNG" , MUTABOR_TOKEN_RETUNING },
{ "HARMONIE"   , MUTABOR_TOKEN_HARMONY   },
{ "LOGIK"      , MUTABOR_TOKEN_LOGIC      },
{ "FORM"       , MUTABOR_TOKEN_FORM       },
{ "MIDIKANAL"  , MUTABOR_TOKEN_MIDICHANNEL },
{ "TASTE"      , MUTABOR_TOKEN_KEY      },
{ "MIDIIN"     , MUTABOR_TOKEN_MIDI_IN    },
{ "MIDIOUT"    , MUTABOR_TOKEN_MIDI_OUT   },
{ "ANSONSTEN"  , MUTABOR_TOKEN_ELSE  },
/* English keywords : */
{ "INTERVAL"   , MUTABOR_TOKEN_INTERVAL  },
{ "ROOT"       , MUTABOR_TOKEN_ROOT     },
{ "TONE"       , MUTABOR_TOKEN_TONE        },
{ "TONESYSTEM" , MUTABOR_TOKEN_TONESYSTEM  },
{ "RETUNING"   , MUTABOR_TOKEN_RETUNING },
{ "PATTERN"    , MUTABOR_TOKEN_HARMONY   },
{ "LOGIC"      , MUTABOR_TOKEN_LOGIC      },
{ "SHIFTED"    , MUTABOR_TOKEN_FORM       },
{ "MIDICHANNEL", MUTABOR_TOKEN_MIDICHANNEL },
{ "KEY"        , MUTABOR_TOKEN_KEY      },
{ "ELSE"       , MUTABOR_TOKEN_ELSE  },
{ NULL         , 0          }
};


#if 0
        char *symbuffer = xmalloc ((size_t)(MAX_IDENTIFIER_LEN + 1));
        int i=0;
        
        do {
            if (c == '\'') c = 'i';
            symbuffer[i++] = c;
            c = toupper(intern_fgetc (quelldatei));
        } while (c != EOF                && 
                 i < MAX_IDENTIFIER_LEN  && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        intern_ungetc (c, quelldatei);
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
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
	    c = intern_fgetc(quelldatei);
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
            c = toupper(c);
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
            anzahl_eingelesene_zeichen ++;

        } while ((c != EOF) && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        intern_ungetc (c, quelldatei);
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
        return MUTABOR_TOKEN_IDENTIFIER;
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

    fatal_error(2,c,yylloc.first_line + 1);
    
    return 0;  /* um Compilerwarnungen zu vermeiden */

    
} /* yylex */

void init_yylex (void)
{
    yylloc.first_line = 0;
    anzahl_eingelesene_zeichen = 0;
}

void yyerror(const char *s) {

/* ignore it ! */

} /* yyerror */



/* END MUT_TAB.C */

/* 
 * \}
 */
