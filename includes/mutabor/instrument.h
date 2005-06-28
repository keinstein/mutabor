/** \file
 ********************************************************************
 * Alles zu Instrumenten.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __INSTRUMENT_H_INCLUDED
#define __INSTRUMENT_H_INCLUDED

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /** Definition der Instrumente als verkettete Liste */
    struct instrument {
      int midi_in;
      int midi_von;
      int midi_bis;
      int midi_umleit;
      struct instrument * next; /**< Nächstes Instrument */
    };

    void get_instrument_dekl (int midi_in, int midi_von, int midi_bis, int midi_umleit,
			      struct instrument ** list_to_insert);

    extern struct instrument     *  list_of_instrumente;
    extern struct instrument     *  list_of_config_instrumente;

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __INSTRUMENT_H_INCLUDED */
