/** \file
 ******************************************************
 * Parser-Generator für Mutabor-Dateien.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/mut.y,v 1.6 2006/03/27 17:03:06 keinstein Exp $
 * \author Rüdiger Krauße <krausze@users.berlios.de>
 * \date $Date: 2006/03/27 17:03:06 $
 * \version $Revision: 1.6 $
 *
 * $Log: mut.y,v $
 * Revision 1.6  2006/03/27 17:03:06  keinstein
 * get rid of heap.h and mutlex.h
 *
 * Revision 1.5  2005/11/03 14:52:10  keinstein
 * *** empty log message ***
 *
 * Revision 1.4  2005/07/20 12:13:47  keinstein
 * CVS-Kopf
 * %pure-parser
 * config.h
 * Header-Dateien ausgemistet
 * yylex neutralisiert.
 * Formatierung
 *
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
%parse-param {void * _self}
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
  /* Relevante Variablen für diese Datei:
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
#include <assert.h>

/* #include "mutabor/heap.h" */
#include "mutabor/bad_decl.h"
#include "mutabor/mut_tab.h"
#include "mutabor/intervalDiff.h"
#include "mutabor/intervalPlaceholder.h"
#include "mutabor/intervalStretch.h"
#include "mutabor/intervalInv.h"
#include "mutabor/tonsystem.h"
#include "mutabor/argument.h"
#include "mutabor/parameter.h"
#include "mutabor/umstimmung.h"
#include "mutabor/taste.h"
#include "mutabor/harmonie.h"
#include "mutabor/logik.h"
#include "mutabor/anweisung.h"
#include "mutabor/instrument.h"
#include "mutabor/parser.h"
#include "mutabor/errors.h"
#include "mutabor/mutfile.h"

  /*  
#undef yylloc
#undef yylval
#undef yylloc
#undef yylval
#define yylloc  mutabor_parser_lloc
#define yylval  mutabor_parser_lval
  */

#define YYLEX_PARAM self->scanner
#define FEHLERZEILE yylloc.first_line
  /*
#define MAX_IDENTIFIER_LEN 80


#define alloca xmalloc
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   / wegen fehlendem alloca in PUREC /

*/


%}

%union {
	double      f_value;        /* for floating point numbers */
	int         integer;        /* for integers */
	char        *identifier;    /* for names */
	void        *object;        /* for data objects */
}


%{
/* #include "mutlex.h" */
#define self ((MUT_CLASS(mutfile)*)_self)
void yyerror(YYLTYPE * locp, void * _self, char const *s);

%}
%token <identifier> IDENTIFIER
%token <f_value> F_NUMBER
%token <integer> INTEGER

%token UNREACHED
%token INTERVALL
%token INTERVALLOBJ
%token WURZEL
%token TON
%token TONOBJ
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

/* 
%type <integer> bezugs_taste
*/
%type <f_value> GLEITKOMMA_ZAHL
%type <object> intervalldekl3 intervalldekl2 intervalsum tondekl2_1 tonsum tondekl3
%destructor { free($$); } IDENTIFIER

/* are in a symbol table, so we don't need any destructor for them
%destructor { mutabor_delete($$); } intervalldekl2
*/

%nonassoc INTERVALL TON TONSYSTEM UMSTIMMUNG HARMONIE LOGIK FORM INSTRUMENT TASTE MIDI_IN MIDI_OUT ANSONSTEN 
%right '='
%left ','
%left '+' '-'
%left INTEGER F_NUMBER
%left '/' ':' WURZEL
%right '(' ')' 

/*  %left '+' '-'  */

%% /* Grammar rules and actions */

start : /* empty */ { yylloc.last_line=1; yylloc.last_column=0; }
        | start intervalldeklaration
        | start tondeklaration
        | start tonsystemdeklaration
/*      	| start umstimmungdeklaration
        | start harmoniedeklaration
        | start logikdeklaration
        | start instrumentdeklaration
        | start error { fatal_error(1,@$.last_line,@$.last_column); }
*/      ;

intervalldeklaration :
        INTERVALL
        | INTERVALL intervalldekl1 ;

intervalldekl1 :
          intervalldekl2_1
          | intervalldekl1 intervalldekl2_1 
      ;

intervalldekl2_1:
           IDENTIFIER '=' intervalsum {		   
		   if ($3) { 
			   char * c;
			   if ((c=MUTABOR_CLASS_FUNCTION(identifier,get_name)($3))) {
			     if (strcmp(c,$1)) {
			       MUT_CLASS(intervalPlaceholder)* alias;
			       alias=MUT_NEW(intervalPlaceholder);
			       MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,alias);
			       MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement)
				                                               (alias,$3);
			       MUTABOR_CLASS_FUNCTION(identifier,set_name)(alias,$1);
			       MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(self->intervals,1);
			     }  else {
				     if (c!=$1) free($1);
			     }
			   } else { 
				   if (MUTABOR_CLASS_FUNCTION(mutfile,check_interval)
				       (_self,$3,$1)) {
					   fatal_error(MUTABOR_ERROR_DOUBLE_INTERVAL,$1);
					   free($1);
				   }
			   }
		   } else free($1);
	   }
      ;

intervalsum : intervalsum '+' intervalsum {
		    $$=MUT_NEW(intervalSum);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)($$,$1);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)($$,$3);
           }
	   | intervalsum '-' intervalsum {
		    $$=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalDiff,setleft)($$,$1);
		    MUTABOR_CLASS_FUNCTION(intervalDiff,setright)($$,$3);
           } 
           | GLEITKOMMA_ZAHL '/' GLEITKOMMA_ZAHL intervalldekl2 {
		   $$=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   ($$,MUTABOR_FLOAT_DIVIDE($1,$3));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)($$,$4);
	   }
           | '/' GLEITKOMMA_ZAHL intervalldekl2 {
		   $$=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   ($$,MUTABOR_FLOAT_DIVIDE(1,$2));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)($$,$3);
	   }
           | intervalldekl2 '/' GLEITKOMMA_ZAHL {
		   $$=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   ($$,MUTABOR_FLOAT_DIVIDE(1,$3));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)($$,$1);
	   }
           | GLEITKOMMA_ZAHL intervalldekl2 {
		   $$=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)($$,$1);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)($$,$2);
	   }
           | '-' intervalldekl2 {
		   $$=MUT_NEW(intervalInv);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		   MUTABOR_CLASS_FUNCTION(intervalInv,setright)
			   ($$,$2);
	   }
           | intervalldekl2
/*	   | intervalldekl2 error {
		   fatal_error(MUTABOR_ERROR_B_MISSING_OPERAND,@$.first_line); 
		   $$=NULL; 
	   }
           | error { fatal_error(MUTABOR_ERROR_B_INVALID_INTERVAL,@$.first_line); }
*/;
           
intervalldekl2 : intervalldekl3 
	   | '(' intervalsum ')' { $$=$2; } 
	   | '(' tondekl3 ',' tondekl3 ')' {
		    $$=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)($$,$2);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)($$,$4);
           } 
;

intervalldekl3 :
           GLEITKOMMA_ZAHL ':' GLEITKOMMA_ZAHL {	    
			    $$=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)
				    ($$,MUTABOR_FLOAT_DIVIDE($1,$3));
		    }

           | GLEITKOMMA_ZAHL WURZEL GLEITKOMMA_ZAHL {
			    $$=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)
				    ($$,MUTABOR_FLOAT_POW($3,MUTABOR_FLOAT_DIVIDE(1,$1)));
	            }
           | IDENTIFIER {
		   $$=MUTABOR_CLASS_FUNCTION(mutfile,get_interval)(_self,$1);
		   free($1);
	   }
/*	   | error {
		   fatal_error(MUTABOR_ERROR_B_MISSING_OPERAND,@$.first_line); 
		   $$=NULL; 
	   }
*/	   ;


/*
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
/ *****
        | IDENTIFIER '=' GLEITKOMMA_ZAHL
                    { get_new_intervall ($1, $3); }
**** /
	| IDENTIFIER '=' KOMPLEX_TON_LIST
			 { get_new_intervall_komplex ($1); }
	| IDENTIFIER '=' error { fatal_error(71,$1); }
        | IDENTIFIER error { fatal_error(70,"'='",FEHLERZEILE); }
      ;
*/
tondeklaration :
        TON
        | TON tondekl1 ;

tondekl1 :
          tondekl2_1
          | tondekl1 tondekl2_1 
      ;

tondekl2_1:
           IDENTIFIER '=' tonsum {		   
		   if ($3) { 
			   char * c;
			   if ((c=MUTABOR_CLASS_FUNCTION(identifier,get_name)($3))) {
			     if (strcmp(c,$1)) {
			       MUT_CLASS(intervalPlaceholder)* alias;
			       alias=MUT_NEW(intervalPlaceholder);
			       MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,alias);
			       MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement)
				                                               (alias,$3);
			       MUTABOR_CLASS_FUNCTION(identifier,set_name)(alias,$1);
			       MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(self->intervals,1);
			     }  else {
					if (c!=$1) free($1);
			     }
			   } else { 
				   if (MUTABOR_CLASS_FUNCTION(mutfile,check_interval)
				       (_self,$3,$1)) {
					   fatal_error(MUTABOR_ERROR_DOUBLE_INTERVAL,$1);
					   free($1);
				   }
			   }
		   } else free($1);
	   }
      ;

tonsum :   tondekl3 '+' intervalsum {
		    $$=MUT_NEW(intervalSum);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)($$,$1);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)($$,$3);
           }
/*           | intervalsum '+' tondekl3 { / * using commutativity * /
		    $$=MUT_NEW(intervalSum);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)($$,$3);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)($$,$1);
           }
*/	   | tondekl3 '-' intervalsum {
		    $$=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)($$,$1);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)($$,$3);
           } 
           | tondekl3 { $$=$1; } 
/*           | tondekl3 error { fatal_error(MUTABOR_ERROR_B_MISSING_OPERAND,@$.first_line); 
		   $$=NULL; 
	   }
           | error { fatal_error(MUTABOR_ERROR_B_INVALID_INTERVAL,@$.first_line); }
*/	  ;
           
tondekl3 :
           GLEITKOMMA_ZAHL {
			    $$=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,$$);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)($$,$1);
           }
           | IDENTIFIER {
	           printf("tondekl3");
		   $$=MUTABOR_CLASS_FUNCTION(mutfile,get_interval)(_self,$1);
		   free($1);
	   }
/*	   | error {
		   fatal_error(MUTABOR_ERROR_B_MISSING_OPERAND,@$.first_line); 
		   $$=NULL; 
	   }
*/   ;

/*
tondeklaration :
        TON tondekl1 ;

tondekl1 :
          / empty /
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
	  / * empty * /
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
/ ******
        | '+'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) 1, $3, $5); }

        | '-'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

        | '+' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( $2, $4, $6); }

        | '-' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
********** /
        ;

KOMPLEX_TON_START :
	  IDENTIFIER
		   { get_new_faktor_anteil ( (double) 1.0 , $1); }

/ ***
        | '-' IDENTIFIER
                   { get_new_faktor_anteil ( (double) -1.0 , $2); }
*** /

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
/ ****
        | '-' GLEITKOMMA_ZAHL IDENTIFIER
                   { get_new_faktor_anteil ( -($2), $3); }
**** /

/ ********
	|  '(' IDENTIFIER ',' IDENTIFIER ')'
	    { get_new_relativ_anteil ( (double) 1, $2, $4); }

        | '-'  '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( (double) -1, $3, $5); }

	|  GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
	    { get_new_relativ_anteil ( $1, $3, $5); }

        | '-' GLEITKOMMA_ZAHL '(' IDENTIFIER ',' IDENTIFIER ')'
            { get_new_relativ_anteil ( - $2, $4, $6); }
********** /
        ;
*/
tonsystemdeklaration :
        TONSYSTEM
	| TONSYSTEM tonsystemdekl1

tonsystemdekl1 :
	tonsystemdekl2_1
        | tonsystemdekl1 tonsystemdekl2_1
      ;
      
tonsystemdekl2_1:
         tonsystemdekl2
      ;

tonsystemdekl2 : 
         IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      intervalsum
/*      |  IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                    '-' KOMPLEX_TON_LIST
                   { get_new_tonsystem_negative ($1, $3); }
*/      ;

tonliste : ton_element | tonliste ',' ton_element ;

ton_element :
          IDENTIFIER      
        | /* empty */  
        | error { fatal_error(73,FEHLERZEILE); }
      ;
/*
tonsystemdeklaration :
        TONSYSTEM tonsystemdekl1 ;

tonsystemdekl1 :
          / * empty * /
        | tonsystemdekl1 tonsystemdekl2_1
      ;
      
tonsystemdekl2_1:
         { init_ton_liste (); } tonsystemdekl2
      ;

tonsystemdekl2 : 
         IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                      intervalsum
                   { get_new_tonsystem ($1, $3); }
/ *      |  IDENTIFIER '=' INTEGER '[' tonliste ']' 
                      { init_komplex_ton_list (); }
                    '-' KOMPLEX_TON_LIST
                   { get_new_tonsystem_negative ($1, $3); }
* /      ;

tonliste : ton_element | tonliste ',' ton_element ;

ton_element :
          IDENTIFIER      { get_new_ton_in_tonsystem ($1); }
        | / * empty * /     { get_new_ton_in_tonsystem (NULL); }
        | error { fatal_error(73,FEHLERZEILE); }
      ;
*/

parameter_liste :      /* allgemein eine Liste von Identifiern */
          IDENTIFIER  
        | parameter_liste ',' IDENTIFIER
        | error { fatal_error(74,FEHLERZEILE); }
        ;

/*
parameter_liste :      / * allgemein eine Liste von Identifiern * /
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

argument_listenelement :        / * allgemein eine Liste von Identifiern
                          oder Kommazahlen * /
          IDENTIFIER      { get_new_name_in_argument_list ($1);   }
        | INTEGER        { get_new_number_in_argument_list ($1); }
        | '-' INTEGER        { get_new_number_in_argument_list (-($2)); }

        ;

*/
umstimmungdeklaration :
	UMSTIMMUNG 
        | UMSTIMMUNG umstimmungs_dekl_1 ;

umstimmungs_dekl_1 :
        umstimmungs_dekl_2 
        | umstimmungs_dekl_1 umstimmungs_dekl_2
      ;

umstimmungs_dekl_2 :
          IDENTIFIER '=' umstimmungs_dekl_3
        | IDENTIFIER '(' parameter_liste ')' '=' umstimmungs_dekl_3 
        ;
        
umstimmungs_dekl_3 :
          umstimmungs_dekl_taste_abs       
        | umstimmungs_dekl_taste_rel      
        | umstimmungs_dekl_breite_abs    
        | umstimmungs_dekl_breite_rel   
        | umstimmungs_dekl_tonhoehe_veraendert 
/*        | umstimmungs_dekl_wiederholung_abs   
        | umstimmungs_dekl_wiederholung_rel  
        | umstimmungs_dekl_umstimmungs_bund 
        | umstimmungs_dekl_umstimmungs_case
        | umstimmungs_dekl_midi_out       
*/        | error {fatal_error(75,FEHLERZEILE);}   
        ;


umstimmungs_dekl_taste_abs :
          INTEGER '[' ']'
        | IDENTIFIER '[' ']'
        ;

umstimmungs_dekl_taste_rel :
          '@' '+' INTEGER '[' ']'
        | '@' '+' IDENTIFIER '[' ']'
        | '@' '-' INTEGER '[' ']'
        | '@' '-' IDENTIFIER '[' ']'
        ;

umstimmungs_dekl_breite_abs :
          '[' '<' '<' INTEGER '>' '>' ']'
        | '[' '<' '<' IDENTIFIER '>' '>' ']'
        ;

umstimmungs_dekl_breite_rel :
          '[' '<' '<' '@' '+' INTEGER '>' '>' ']'
        | '[' '<' '<' '@' '+' IDENTIFIER '>' '>' ']'
        | '[' '<' '<' '@' '-' INTEGER '>' '>' ']'
        | '[' '<' '<' '@' '-' IDENTIFIER '>' '>' ']'
        | '[' '<' '<' '@' '*' INTEGER '>' '>' ']'
        | '[' '<' '<' '@' '*' IDENTIFIER '>' '>' ']'
        | '[' '<' '<' '@' '/' INTEGER '>' '>' ']'
        | '[' '<' '<' '@' '/' IDENTIFIER '>' '>' ']'
        ;

umstimmungs_dekl_tonhoehe_veraendert :
          '[' 
/*          nonempty_umstimm_expression_list ']'
*/        ;
/*	
umstimmungdeklaration :
        UMSTIMMUNG umstimmungs_dekl_1 ;

umstimmungs_dekl_1 :
          / * empty * /
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

/ * Eine leere Liste von Umstimm-expression kollidiert syntaktisch
   mit "umstimmungs-wiederholung" oder "umstimmungs-bund" * /
        
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
          / * empty * /
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
          / * empty * /      { $$ = -1; }
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
          / * empty * / {}
        | logik_dekl_1 { init_ausloeser ();
                         / * für die Anfangsausloesung der Logik * /
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
          / * empty * / {}
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
        | TASTE IDENTIFIER { get_ausloeser_taste ($2); }
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
          / * empty * / {}
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

*/        
GLEITKOMMA_ZAHL:
           F_NUMBER  { $$ = $1; }
        |  INTEGER   { $$ = (double) $1; }
        ;

%%        
void yyerror(YYLTYPE * locp, void * _self, char const *s) {
  fprintf(stderr,"\n%s at line %d col %d\n",s,locp->first_line,locp->first_column);
  /*
  return 1;
  */
/* ignore it ! */
  
} /* yyerror */

/* END MUT_TAB.C */
