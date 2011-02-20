/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Interval.h,v 1.5 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Interval.h,v $
 * Revision 1.5  2011/02/20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Intervallberechnungen
// ------------------------------------------------------------------

#if ! defined (__INTERVAL_H_INCLUDED)
#define __INTERVAL_H_INCLUDED

int intervall_list_laenge (struct intervall *list);

void berechne_intervalle_absolut (struct intervall * list_of_intervalle);

void check_komplex_intervall (struct komplex_intervall * liste,

                              const char * konstrukt_name);

#endif


///\}
