/** \file
 ********************************************************************
 * Alles zu Instrumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/instrument.h,v 1.2 2005/07/08 14:53:24 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/08 14:53:24 $
 * \version $Revision: 1.2 $
 * \log $Log: instrument.h,v $
 * \log Revision 1.2  2005/07/08 14:53:24  keinstein
 * \log Neu:
 * \log 	Kopf
 * \log
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
