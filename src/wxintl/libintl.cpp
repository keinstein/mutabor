/** \file               -*- C++ -*-
********************************************************************
* Glue code to use wxWidgets translation mechanism
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/wxintl/libintl.h"

// system headers which do seldom change
#include <locale.h>
#include <map>
#include "wx/intl.h"

#define muT(x) x

/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#undef STUB
#define STUB \
	assert(false)

extern "C" {

	const char * wxwidgets_sgettext(const char * msgid)
 	{
		return wxwidgets_gettext(msgid);
	}

	const char * wxwidgets_dgettext(const char * domainname, 
					const char * msgid)
	{
		return wxwidgets_gettext(domainname,msgid);
	}

#if 0
	const char * wxwidgets_dcgettext(const char * domainname, 
					 const char * msgid,
					 int category)
		return wxwidgets_gettext(domainname,msgid,catogory);
#endif

	const char *wxwidgets_sngettext (const char * msgid1, 
					 const char * msgid2,
					 unsigned long int n)
	{
		return wxwidgets_gettext(msgid1,msgid2,n);
	}

	const char *wxwidgets_dngettext (const char * /* domainname */,
					 const char * msgid1,
					 const char * msgid2,
					 unsigned long int n)
	{
		return wxwidgets_gettext(msgid1,msgid2,n);
	}

#if 0
	/* Similar to `dcgettext' but select the plural form corresponding to the
	   number N.  */
	const char *wxwidgets_dcngettext (const char * domainname, const char * msgid1,
					  const char * msgid2, unsigned long int n,
					  int __category)
		__attribute_format_arg__ (2) __attribute_format_arg__ (3);
#endif
	/* Set the current default message catalog to DOMAINNAME.
	   If DOMAINNAME is null, return the current default.
	   If DOMAINNAME is "", reset to the default of "messages".  */
	char *wxwidgets_textdomain (const char *__domainname) throw()
	{
		if (__domainname) {
			wxGetLocale()->AddCatalog(muT(__domainname));
		} else {
			STUB;
		} 
		return const_cast<char *>("");
	}

	/* Specify that the DOMAINNAME message catalog will be found
	   in DIRNAME rather than in the system locale data base.  */
	char *wxwidgets_bindtextdomain (const char * /*__domainname*/,
					const char *__dirname) throw()
	{
		if (__dirname)
			wxGetLocale()->AddCatalogLookupPathPrefix(muT(__dirname));
		else {
			STUB;
		}
		return const_cast<char *>("");
	}

#if 0
	/* Specify the character encoding in which the messages from the
	   DOMAINNAME message catalog will be returned.  */
	char *wxwidgets_bind_textdomain_codeset (const char *__domainname,
				       const char *__codeset) __THROW
	{
	}
#endif
						
}
#include <string>

/* cache the results as we must provide pointers to valid strings,
   while ToUTF8 returns only scoped pointers */

struct wxwidgets_gettext_mapkey {
	std::string domain;
	std::string key;
	long unsigned int count;
	//	int category;

	wxwidgets_gettext_mapkey(const std::string & k,
				 long unsigned int c = 1/*,
							  cat = LC_MESSAGES*/):domain(),
									       key(k),
									       count(c)/*,
											 category(cat)*/ {}

	wxwidgets_gettext_mapkey(const std::string & d,
				 const std::string & k,
				 long unsigned int c = 1/*,
							  cat = LC_MESSAGES*/):domain(d),
									       key(k),
									       count(c)/*,
											 category(cat)*/ {}
	bool operator < (const wxwidgets_gettext_mapkey & o) const {
		//		if (category != o.category) return (category < o.category);
		if (count != o.count) return (count < o.count);
		if (domain < o.domain) return true;
		if (domain > o.domain) return false;
		return (key < o.key);
	}
};

class wxwidgets_gettext_result {
	const char * ptr;
public:
	wxwidgets_gettext_result(): ptr(NULL) {}
	~wxwidgets_gettext_result() { free(const_cast<char *>(ptr)); }
	wxwidgets_gettext_result & operator = (const char * data) {
		ptr = strdup(data);
		return *this;
	}
	operator const char * () { return ptr; }
};

typedef std::map<wxwidgets_gettext_mapkey, wxwidgets_gettext_result> wxwidgets_gettext_map;

static wxwidgets_gettext_map cache;

const char * wxwidgets_gettext(const std::string & msgid)
{
	wxwidgets_gettext_mapkey key(msgid);
	wxwidgets_gettext_map::iterator i = cache.find(key);
	if (i != cache.end()) {
		return i->second;
	}
	cache[key] = wxString(wxGetTranslation(muT(msgid))).ToUTF8();
	return cache[key];
}

const char * wxwidgets_gettext(const std::string & domainname, 
			       const std::string & msgid)
{
	wxwidgets_gettext_mapkey key(domainname,msgid);
	wxwidgets_gettext_map::iterator i = cache.find(key);
	if (i != cache.end()) {
		return i->second;
	}
	cache[key] = wxString(wxGetTranslation(muT(msgid),
					       muT(domainname))).ToUTF8();
	return cache[key];
}
/*
  const char * wxwidgets_gettext(const std::string & domainname, 
  const std::string & msgid,
  int category)
  {
  wxwidgets_gettext_mapkey key(domainname,msgid,1,category);
  wxwidgets_gettext_map::iterator i = cache.find(key);
  if (i != cache.end()) {
  return i->second;
  }
  cache[key] = strdup(wxGetTranslation(domainname,msgid,category).ToUTF8());
  }
*/

const char *wxwidgets_gettext (const std::string & msgid1, 
			       const std::string & msgid2,
			       unsigned long int n)
{
	wxwidgets_gettext_mapkey key(msgid1,n);
	wxwidgets_gettext_map::iterator i = cache.find(key);
	if (i != cache.end()) {
		return i->second;
	}
	cache[key] = wxString(wxGetTranslation(muT(msgid1),
					       muT(msgid2),n)).ToUTF8();
	return cache[key];
}

const char *wxwidgets_gettext (const std::string & domainname, 
			       const std::string & msgid1,
			       const std::string & msgid2,
			       unsigned long int n) 
{
	wxwidgets_gettext_mapkey key(domainname,msgid1,n);
	wxwidgets_gettext_map::iterator i = cache.find(key);
	if (i != cache.end()) {
		return i->second;
	}
	cache[key] = wxString(wxGetTranslation(muT(msgid1),
					       muT(msgid2),
					       n,muT(domainname))).ToUTF8();
	return cache[key];
}

/*
  const char *wxwidgets_gettext (const std::string & domainname, 
  const std::string & msgid1,
  const std::string & msgid2,
  unsigned long int n,
  int category)
  __attribute_format_arg__ (2) __attribute_format_arg__ (3);

*/


///\}
