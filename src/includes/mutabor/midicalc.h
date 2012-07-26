/** \file
 ********************************************************************
 * MIDI-Berechnungen.
 *
 * $Id: midicalc.h,v 1.3 2005/11/03 14:33:36 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:33:36 $
 * \version $Revision: 1.3 $
 *
 * $Log: midicalc.h,v $
 * Revision 1.3  2005/11/03 14:33:36  keinstein
 * new header
 * includes corrected
 * interpreter data structures and functions
 *
 ********************************************************************/

#ifndef __MIDICALC_H_INCLUDED
#define __MIDICALC_H_INCLUDED

#ifdef HAVE_MATH_H
# include<math.h>
#endif

/* Zur Umrechnung in die Midi-Darstellung
   als Gleitpunktzahl in long.
   Erstes Byte Vorkommastellen, drei Bytes Nachkommastellen. */
#define DOUBLE_TO_LONG(x) ((long int) ((x) * (1L<<24)))

/** Frequenz nach Midi umrechnen. 
 * Es gilt: \f[0.05776226504666210908=\ln\left(\sqrt[12]2\right)\f].
 * \param[in] x Freqenz
 * \return erweiterte Midi-Tastennummer
 */
#define FREQUENZ_TO_MIDI(x) (log((x)/440.0)/0.05776226504666210908 + 69)

/** Faktor nach Midi umrechnen.
 * Es gilt: \f[17.31234049066756089=\frac{12}{\ln 2}\f].
 * \param[in] x Faktor
 * \return erweiterte Midi-Tastennummer
 */
#define FAKTOR_TO_MIDI(x) (17.31234049066756089 * log(x))

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /** Einfach verkettete Liste mit ganzzahligen Midi-Codes. */
    struct midiliste {
      int midi_code;
      struct midiliste * next;
    };

    void init_integersequenz (void);
    void get_new_integer_in_integersequenz (int wert);
    int midi_list_laenge (struct midiliste *list);
    struct midiliste * get_last_integersequenz (void);
    int * create_midi_scan_liste (struct midiliste * lauf);
    
    void print_integersequenz (struct midiliste * this_);

#ifdef __cplusplus 
  }
}
#endif

#endif /* __MIDICALC_H_INCLUDED */
