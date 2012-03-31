/** \file
 ********************************************************************
 * Interval calculations
 *
 * $Id: interval.h,v 1.7 2005/11/14 14:35:49 keinstein Exp $
 * \author R.Krauße
 *         Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/14 14:35:49 $
 * \version $Revision: 1.7 $
 * 
 * $Log: interval.h,v $
 * Revision 1.7  2005/11/14 14:35:49  keinstein
 * make distcheck happy
 *
 * Revision 1.2  2005/11/10 16:16:59  keinstein
 * working distcheck
 *
 * Revision 1.1  2005/11/03 13:57:46  keinstein
 * basic interval class
 *
 ********************************************************************/

#if ! defined (__INTERVAL_H_INCLUDED)
#define __INTERVAL_H_INCLUDED

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "mutabor/identifier.h"
#include "mutabor/bad_decl.h"

    /** Interval class. */

struct mutabor_class_interval {
    struct mutabor_class_identifier _; /**< Parent class */
    MUTABOR_FLOAT factor; 
};

struct mutabor_virttable_interval {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); 
    void * (*destructor)(void * _self); /**< Destructor for deleting the class. */
    int (*compare)(void * one, void * two); 
    char * (*tostring)(void * _self); 
    void * (*check_cycle)(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list); /**< checks, if _self depends somehow on _identifier. */
    void (*precalculate)(void * _self); /**< precalculate the dependencies */
};

extern const void * mutabor_object_interval;


#define mutabor_cls_interval_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_interval_set_name mutabor_cls_identifier_set_name

#define mutabor_cls_interval_get_name mutabor_cls_identifier_get_name
extern void mutabor_cls_interval_set_factor(void * _self,MUTABOR_FLOAT value);

#ifdef OLD_MUTABOR_CLASSES
#define MUTABOR_CLASS_DEFINITIONS_interval(class) \
  PARENT(class,identifier)\
  FIELD(class,MUTABOR_FLOAT,value)\
  OVERRIDE(class, void *, constructor, void * _self) \
  OVERRIDE(class, void *, destructor, void * _self) \
  OVERRIDE(class, int, compare, void * one, void * two) \
  OVERRIDE(class, char *, tostring,void * _self)

MUTABOR_DECLARE_CLASS(interval);
#endif


    /** Old Functionality */


    /*********  Definition der Intervalle als verkettete Liste ********/

    /** Intervalle können absolut oder über mehrere Sprünge angegeben werden. */
    enum intervall_typ {intervall_absolut, intervall_komplex};

    /** Folge von Intervallen, die zum Grundton addiert werden. */
    struct komplex_intervall {
      double faktor; /**< exponent des Frequenzfaktors */
      char * name; /**< Name des Intervalles */
      struct komplex_intervall * next; /**< Liste der Einzel-Intervalle */
    };

    /** Definition der Intervalle als einfach verkettete Liste.
     * 
     */ 
    struct intervall {
      char * name; /**< Name des Intervalls */
      enum intervall_typ intervall_typ; /**< Typ des Intervalles */
      union {
        struct {
	  double intervall_wert; /**< Wert eines absoluten Intervalles */
        } intervall_absolut; /**< Daten des absoluten Intervalles */
        struct {
	  struct komplex_intervall * komplex_liste; /**< Liste der Intervalle */
        } intervall_komplex; /**< Daten eines zusammengesetzten Intervalles */
      } u; /**< Daten des Intervalles */
      struct intervall *next; /**< Nächstes in der Liste */
    };

    void get_new_intervall (char * name, double wert);
    void get_new_intervall_komplex (char * name);
    double get_wert_komplex_intervall (struct komplex_intervall * intervall);
    void get_new_faktor_anteil (double f, char *name);

    struct intervall * get_intervall (char * name,
                                      struct intervall * liste);
    int intervall_list_laenge (struct intervall *list);
    void berechne_intervalle_absolut (struct intervall * list_of_intervalle);
    void check_komplex_intervall (struct komplex_intervall * liste,
				  char * konstrukt_name);
    double get_komplex_faktor (struct komplex_intervall * lauf);

    struct komplex_intervall * get_last_komplex_intervall (void);
    extern struct intervall      *  list_of_intervalle;

#ifdef __cplusplus
  }
}
#endif

#endif
