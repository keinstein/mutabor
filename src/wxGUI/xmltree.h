/** \file  -*- C++ -*-
***********************************************************************
* implementation class for tree like storage using wxConfigBase based
* classes.
*
* \author T. Schlemmer <keinstein@users.berlios.de>
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
*
********************************************************************
* \addtogroup config
* \{
********************************************************************/
#if (!defined(MUWX_XMLTREE_H) && !defined(PRECOMPILE))		      \
	|| (!defined(MUWX_XMLTREE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_XMLTREE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Box.h"
#include "src/kernel/treestorage.h"

#ifndef MUWX_XMLTREE_H_PRECOMPILED
#define MUWX_XMLTREE_H_PRECOMPILED

#include <stack>
#include "wx/xml/xml.h"
#include "boost/lexical_cast.hpp"

namespace mutaborGUI {
	class xmltree:public mutabor::tree_storage,
		      public wxXmlDocument
	{
		typedef wxXmlNode node_type;
		typedef wxXmlProperty prop_type;
		typedef wxXmlDocument doc;
		///< configuration object
		//	bool deleteconfig; ///< true if the config is private and must be deleted on deletion

		/// structure describing the current state
		struct state {
			state(node_type * n, wxString p): node(n),
							     path(p)
			{}

			node_type * node;
			wxString path;

			bool operator == (const state & s) const
			{
				bool retval = node == s.node;
				mutASSERT(retval == (path == s.path));
				return retval;
			}
		};
		std::stack<state> states;
		bool create_tree;

		node_type * current_node;
	public:
		xmltree(wxString rootname,
			bool create=true);

		virtual ~xmltree()
		{
		}

		virtual bool Load(const wxString& filename,
				  const wxString& encoding = wxT("UTF-8"),
				  int flags = wxXMLDOC_NONE);

		virtual long Read(const std::string& key, long defval) {
			return Read (wxString::FromUTF8(key.c_str()), defval);
		}
		virtual double Read(const std::string& key, double defval) {
			return Read (wxString::FromUTF8(key.c_str()), defval);
		}
		virtual int Read(const std::string& key, int defval) {
			return Read (wxString::FromUTF8(key.c_str()), defval);
		}
		virtual bool Read(const std::string& key, bool defval) {
			return Read (wxString::FromUTF8(key.c_str()), defval);
		}
		virtual long Read(const wxString& key, long defval);
		virtual double Read(const wxString& key, double defval);
		virtual int Read(const wxString& key, int defval);
		virtual bool Read(const wxString& key, bool defval);
		virtual std::string Read(const std::string& key, const std::string& defval) {
			return (const char *)Read(wxString::FromUTF8(key.c_str()),
						  wxString::FromUTF8(defval.c_str())).ToUTF8();
		}
		virtual wxString Read(const wxString& key, const wxString& defval);

		virtual void Write (const std::string& key, long value) {
			Write (wxString::FromUTF8(key.c_str()), value);
		}
		virtual void Write (const std::string& key, double value) {
			Write (wxString::FromUTF8(key.c_str()), value);
		}
		virtual void Write (const std::string& key, int value) {
			Write (wxString::FromUTF8(key.c_str()), value);
		}
		virtual void Write(const std::string& key, bool value) {
			Write (wxString::FromUTF8(key.c_str()), value);
		}
		virtual void Write (const wxString& key, long value);
		virtual void Write (const wxString& key, double value);
		virtual void Write (const wxString& key, int value);
		virtual void Write(const wxString& key, bool value);
		virtual void Write (const std::string& key, const std::string& value) {
			Write (wxString::FromUTF8(key.c_str()),
			       wxString::FromUTF8(value.c_str()));
		}
		virtual void Write (const wxString& key, const wxString& value);

 		virtual bool HasGroup(const std::string& subdir) const
		{
			return HasGroup(wxString::FromUTF8(subdir.c_str()));
		}
 		virtual bool HasGroup(const wxString& subdir) const
		{
			return const_cast<xmltree *>(this)->HasGroup(subdir);
		}
		virtual bool HasGroup(const std::string& subdir) {
			return HasGroup(wxString::FromUTF8(subdir.c_str()));
		}
		virtual bool HasGroup(const wxString& subdir);
		virtual void toLeaf(const std::string& subdir) {
			toLeaf(wxString::FromUTF8(subdir.c_str()));
		}
		virtual void toLeaf(const std::string& name, int id) {
			toLeaf(wxString::FromUTF8(name.c_str()),id);
		}
		virtual void toLeaf(const wxString& subdir);
		virtual void toLeaf(const wxString& name, int id);
		virtual int toFirstLeaf(const std::string& name) {
			return toFirstLeaf(wxString::FromUTF8(name.c_str()));
		}
		virtual int toFirstLeaf(const wxString & name) {
			wxString id;
			if (toFirstLeaf(name,id) == wxNOT_FOUND)
				return wxNOT_FOUND;
			long i;
			if (id.ToLong(&i)) return (int)i;
			else return wxNOT_FOUND;
		}
		virtual int toFirstLeaf(const std::string& name, std::string& id) {
			wxString id2 = wxString::FromUTF8(id.c_str());
			int retval = toFirstLeaf(wxString::FromUTF8(name.c_str()),
					   id2);
			id = id2.ToUTF8();
			return retval;
		}
		virtual int toFirstLeaf(const wxString& name, wxString& id);
		virtual int toNextLeaf(const std::string& name) {
			return toNextLeaf(wxString::FromUTF8(name.c_str()));
		}
		virtual int toNextLeaf(const wxString& name)
		{
			wxString id;
			if (toNextLeaf(name,id) == wxNOT_FOUND)
				return wxNOT_FOUND;
			long i;
			if (id.ToLong(&i)) return (int)i;
			else return wxNOT_FOUND;
		}
		virtual int toNextLeaf(const std::string& name, std::string& id) {
			wxString id2 = wxString::FromUTF8(id.c_str());
			int retval = toNextLeaf(wxString::FromUTF8(name.c_str()),
				   id2);
			id = id2.ToUTF8();
			return retval;
		}
		virtual int toNextLeaf(const wxString& name, wxString& id);
		virtual void toParent(unsigned int count = 1);

		virtual std::string GetPath() {
			return (const char *)GetwxPath().ToUTF8();
		}
		virtual wxString GetwxPath();
		virtual void SetPath(const std::string& path) {
			SetPath(wxString::FromUTF8(path.c_str()));
		}
		virtual void SetPath(const wxString& path);

		/// Delete an entry
		/**
		 *  \argument entry path to the entry that shall be deleted
		 */
		virtual void DeleteEntry(const std::string& path) {
			DeleteEntry(wxString::FromUTF8(path.c_str()));
		}
		virtual void DeleteEntry(const wxString& path);
		
		/// Delete an entire group with all childs
		/**
		 *  \argument group path to the entry that shall be deleted
		 */
		virtual void DeleteGroup(const std::string& path) {
			DeleteGroup(wxString::FromUTF8(path.c_str()));
		}
		virtual void DeleteGroup(const wxString& path);

	protected:
		/** 
		 * Get an XML attribute name of the node.
		 * 
		 * \param name   name of the property.
		 * \param create shall it be created?
		 * 
		 * \return a pointer to the corresponding object.
		 *
		 * \note as we normalize the name anyway, we copy the
		 * object during the call.
		 */
		wxXmlProperty * GetProperty (wxString name,
					     bool create);
		/** 
		 * Set an XML attribute of the node.
		 * 
		 * \param name   name of the property.
		 * \param value  new value
		 * 
		 * \return a pointer to the corresponding object.
		 *
		 * \note as we normalize the name anyway, we copy the
		 * object during the call.
		 */
		wxXmlProperty * SetProperty (wxString name,
					     const wxString& value);

		void NormalizeName(wxString & name);


	};

}

#endif //MUTABOR_XMLTREE_H_PRECOMPILED
#endif //MUTABOR_XMLTREE_H


///\}
