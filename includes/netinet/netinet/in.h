/** \file
 ************************************************************
 * replacement for netinet/in.h used by flex lexers.
 * 
 * $Id: in.h,v 1.1 2006/03/27 16:40:12 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2006/03/27 16:40:12 $
 *
 * $Log: in.h,v $
 * Revision 1.1  2006/03/27 16:40:12  keinstein
 * first submit
 *
 ************************************************************/

#ifdef HAVE_WINSOCK2_H
#  include <winsock2.h>
#endif
