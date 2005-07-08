/** \file
 ********************************************************************
 * MIDI-Berechnungen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __MIDICALC_H_INCLUDED
#define __MIDICALC_H_INCLUDED

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

    void print_integersequenz (struct midiliste * this_);

#ifdef __cplusplus 
  }
}
#endif

#endif /* __MIDICALC_H_INCLUDED */
