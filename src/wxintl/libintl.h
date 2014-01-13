/** \file               -*- C++ -*-
 ********************************************************************
 * Glue code to use wxWidgets translation mechanism
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup kernel
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_WXINTL_LIBINTL) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_WXINTL_LIBINTL_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_WXINTL_LIBINTL
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef SRC_WXINTL_LIBINTL_PRECOMPILED
#define SRC_WXINTL_LIBINTL_PRECOMPILED

// system headers which do seldom change

#ifdef __cplusplus 
extern "C" {
#endif
#ifndef __cplusplus
#define wxwidgets_gettext(msgid) wxwidgets_sgettext(msgid)
#endif

	extern const char * wxwidgets_sgettext(const char * msgid)
		__attribute_format_arg__ (1);
	extern const char * wxwidgets_dgettext(const char * domainname, 
					       const char * msgid)
		__attribute_format_arg__ (2);
#if 0
	extern const char * wxwidgets_dcgettext(const char * domainname, 
						const char * msgid,
						int category)
		__attribute_format_arg__ (2);
#endif

	
#ifndef __cplusplus
#define wxwidgets_ngettext(msgid1,msgid2,n) wxwidgets_sngettext(msgid1,msgid2,n)
#endif
	/* Similar to `gettext' but select the plural form corresponding to the
	   number N.  */
	extern const char *wxwidgets_sngettext (const char * msgid1, const char * msgid2,
					       unsigned long int n)
		__attribute_format_arg__ (1) __attribute_format_arg__ (2);

	/* Similar to `dgettext' but select the plural form corresponding to the
	   number N.  */
	extern const char *wxwidgets_dngettext (const char * domainname, const char * msgid1,
						const char * msgid2, unsigned long int n)
		__attribute_format_arg__ (2) __attribute_format_arg__ (3);

#if 0
	/* Similar to `dcgettext' but select the plural form corresponding to the
	   number N.  */
	extern const char *wxwidgets_dcngettext (const char * domainname, const char * msgid1,
						 const char * msgid2, unsigned long int n,
						 int __category)
		__attribute_format_arg__ (2) __attribute_format_arg__ (3);
#endif


/* Set the current default message catalog to DOMAINNAME.
   If DOMAINNAME is null, return the current default.
   If DOMAINNAME is "", reset to the default of "messages".  */
extern char *wxwidgets_textdomain (const char *__domainname) ;

/* Specify that the DOMAINNAME message catalog will be found
   in DIRNAME rather than in the system locale data base.  */
extern char *wxwidgets_bindtextdomain (const char *__domainname,
			     const char *__dirname);

#if 0
/* Specify the character encoding in which the messages from the
   DOMAINNAME message catalog will be returned.  */
extern char *bind_textdomain_codeset (const char *__domainname,
				      const char *__codeset) ;
#endif


						
#ifdef __cplusplus 
}
#include <string>


extern const char *  wxwidgets_gettext(const std::string &  msgid);
extern const char * wxwidgets_gettext(const std::string & domainname, 
				      const std::string & msgid);
#if 0
extern const char * wxwidgets_gettext(const std::string & domainname, 
				      const std::string & msgid,
				      int category);
#endif

/* Similar to `gettext' but select the plural form corresponding to the
   number N.  */
extern const char *wxwidgets_gettext (const std::string & msgid1, 
				      const std::string & msgid2,
				      unsigned long int n);

/* Similar to `dgettext' but select the plural form corresponding to the
   number N.  */
extern const char *wxwidgets_gettext (const std::string & domainname, 
				      const std::string & msgid1,
				      const std::string & msgid2,
				      unsigned long int n);

#if 0
/* Similar to `dcgettext' but select the plural form corresponding to the
   number N.  */
extern const char *wxwidgets_gettext (const std::string & domainname, 
				      const std::string & msgid1,
				      const std::string & msgid2,
				      unsigned long int n,
				      int category);
#endif


//#define wxwidgets_gettext wxwidgets_pgettext
const char * wxwidgets_gettext(const char * msgid)
	__attribute_format_arg__ (1) ;
inline const char * wxwidgets_gettext(const char * msgid)
{
	std::string m(msgid);
	return wxwidgets_gettext(m);
}
const char * wxwidgets_gettext(const char * domainname, 
				      const char * msgid)
	__attribute_format_arg__ (2);
inline const char * wxwidgets_gettext(const char * domainname, 
				      const char * msgid)
{
	std::string d(domainname), m(msgid);
	return wxwidgets_gettext(d,m);
}

#if 0
const char * wxwidgets_gettext(const char * domainname, 
				      const char * msgid,
				      int category)
	__attribute_format_arg__ (2);
inline const char * wxwidgets_gettext(const char * domainname, 
				      const char * msgid,
				      int category)
{
	std::string d(domainname), m(msgid);
	return wxwidgets_gettext(d,m,category);
}
#endif


/* Similar to `gettext' but select the plural form corresponding to the
   number N.  */
 const char *wxwidgets_gettext (const char * msgid1, 
				      const char * msgid2,
				      unsigned long int n)
	 __attribute_format_arg__ (1) __attribute_format_arg__ (2);
inline const char *wxwidgets_gettext (const char * msgid1, 
				      const char * msgid2,
				      unsigned long int n)
{
	std::string m1(msgid1), m2(msgid2);
	return wxwidgets_gettext(msgid1,msgid2,n);
}

/* Similar to `dgettext' but select the plural form corresponding to the
   number N.  */
const char *wxwidgets_gettext (const char * domainname, 
				      const char * msgid1,
				      const char * msgid2, unsigned long int n)
	__attribute_format_arg__ (2) __attribute_format_arg__ (3);
inline const char *wxwidgets_gettext (const char * domainname, 
				      const char * msgid1,
				      const char * msgid2, unsigned long int n)
{
	std::string d(domainname), m1(msgid1), m2(msgid2);
	return wxwidgets_gettext(m1,m2,n);
}

#if 0
/* Similar to `dcgettext' but select the plural form corresponding to the
   number N.  */
const char *wxwidgets_gettext (const char * domainname, 
				      const char * msgid1,
				      const char * msgid2, 
				      unsigned long int n,
				      int category)
	__attribute_format_arg__ (2) __attribute_format_arg__ (3);
extern const char *wxwidgets_gettext (const char * domainname, 
				      const char * msgid1,
				      const char * msgid2, 
				      unsigned long int n,
				      int category)
{
	std::string d(domainname), m1(msgid1), m2(msgid2);
	return wxwidgets_gettext(m1,m2,n,category);
}
#endif



#endif
#endif // precompiled
#endif // header loaded


///\}
