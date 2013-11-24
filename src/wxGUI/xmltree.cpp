/** \file
***********************************************************************
* abstract class for tree like storage
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
********************************************************************
* \addtogroup config
* \{
********************************************************************/
#include "src/kernel/Defs.h"
#include "src/wxGUI/xmltree.h"
#include "wx/tokenzr.h"

namespace mutaborGUI {

	xmltree::xmltree(wxString rootname,
			 bool create):tree_storage(),
					   doc(),
					   states(),
					   create_tree(create),
					   current_node(doc::GetRoot())
	{
		if (!create) return;
		states.push(state(NULL,_T("/")));
		toLeaf(_T("/")+rootname);
	}

	bool xmltree::Load(const wxString& filename,
			  const wxString& encoding,
			  int flags) {
		while(!states.empty())
			states.pop();
		current_node = NULL;
		wxXmlNode * tmp = GetRoot();
		SetRoot(NULL);
		delete tmp;
		if (doc::Load(filename,encoding,flags)) {
			current_node = GetRoot();
			states.push(state(NULL,_T("/")));
			if (current_node) {
				toLeaf(_T("/")+current_node->GetName());
				return true;
			}
		}
		return false;
	}


	long xmltree::Read(const mutStringRef key, long defval)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return defval;
		const wxString & val = prop->GetValue();
		long retval;
		val.ToLong(&retval);
		return retval;
	}

	double xmltree::Read(const mutStringRef key, double defval)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return defval;
		const wxString & val = prop->GetValue();
		double retval;
		val.ToDouble(&retval);
		return retval;
	}

	int xmltree::Read(const mutStringRef key, int defval)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return defval;
		const wxString & val = prop->GetValue();
		long retval;
		val.ToLong(&retval);
		return retval;
	}

	bool xmltree::Read(const mutStringRef key, bool defval)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return defval;
		const wxString & val = prop->GetValue();
#ifdef DEBUG
		long tmp;
		mutASSERT(!(wxString(_T("false")).ToLong(&tmp)));
#endif
		long retval;
		if (val.ToLong(&retval)) return retval;
		return val == _T("true");
	}

	mutString xmltree::Read(const mutStringRef key, const mutStringRef defval)
	{
		if (key == _T("name")) {
			wxXmlProperty * prop = GetProperty(key, true);
			if (!prop) return defval;
			const wxString & val = prop->GetValue();
			return val;
		}
		if (!current_node) return defval;
		wxString name = key;
		NormalizeName(name);
		wxXmlNode * node = current_node->GetChildren();
		while (node && node -> GetName() != name) {
			node = node->GetNext();
		}
		if (!node) return defval;
		return node->GetNodeContent();
	}

	void xmltree::Write (const mutStringRef key, long value)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return;
		prop->SetValue(wxString::Format("%ld",value));
	}

	void xmltree::Write (const mutStringRef key, double value)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return;
		prop->SetValue(wxString::Format("%20g",value));
	}

	void xmltree::Write (const mutStringRef key, int value)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return;
		prop->SetValue(wxString::Format("%d",value));
	}

	void xmltree::Write (const mutStringRef key, bool value)
	{
		wxXmlProperty * prop = GetProperty(key, true);
		if (!prop) return;
		prop->SetValue(value?"true":"false");
	}

	void xmltree::Write (const mutStringRef key, const mutStringRef value)
	{
		if (key == "name") {
			wxXmlProperty * prop = GetProperty(key, true);
			if (!prop) return;
			prop->SetValue(value);
		} else {
			wxString keyname = key;
			NormalizeName(keyname);
			wxXmlNode * node = new node_type(current_node,
							 wxXML_ELEMENT_NODE,
							 keyname);

			new node_type(node,
				      wxXML_TEXT_NODE,
				      keyname,
				      value);
		}
	}

	bool xmltree::HasGroup(const mutStringRef subdir)
	{
		wxString sanitized_name = subdir;
		NormalizeName(sanitized_name);
		node_type * node = current_node;
		bool create = create_tree;
		create_tree = false;
		SetPath(sanitized_name);
		bool retval = current_node;
		create_tree = create;
		current_node = node;
		return retval;
	}

	void xmltree::toLeaf(const mutStringRef subdir)
	{
		wxString sanitized_name = subdir;
		NormalizeName(sanitized_name);
		DEBUGLOG(config,_T("going to group '%s'"),sanitized_name.c_str());
#if 0
		mutASSERT(sanitized_name.Find('/') == wxNOT_FOUND);
		mutASSERT(sanitized_name != _T(".."));
		if (sanitized_name.Find('/') != wxNOT_FOUND || sanitized_name == _T("..")) {
			UNREACHABLEC;
			return;
		}
#endif
		SetPath(sanitized_name);
		state newstate(current_node,sanitized_name);

		DEBUGLOG(config,_T("setting path to '%s'"),(sanitized_name).c_str());
		states.push(newstate);
		DEBUGLOG(config,_T("current path = '%s', newstate(node = %p)"),
			 GetPath().c_str(), newstate.node);
	}

	void xmltree::toLeaf(const mutStringRef name, int id)
	{
		wxString sanitized_name = name;
		NormalizeName(sanitized_name);
		if (!current_node) return;
		DEBUGLOG(config,_T("going to group '%s' with id %d"),sanitized_name.c_str(),id);
		node_type * node = current_node;
		bool create = create_tree;
		create_tree = false;
		SetPath(sanitized_name);
		create_tree = create;
		wxString idstr = wxString::Format(_T("%d"),id);
		node_type * old_node = current_node;
		wxString idval;
		if (!current_node) {
			current_node = node;
			toLeaf(sanitized_name);
			if (current_node) {
#if wxCHECK_VERSION(2,9,0)
				current_node->SetAttributes(new wxXmlAttribute(_T("Id"),idstr));
#else
				current_node->SetProperties(new wxXmlProperty(_T("Id"),idstr));
#endif
			}
			return;
		}
		node = current_node;
#if wxCHECK_VERSION(2,9,0)
		idval = node->GetAttribute(_T("Id"),_T(""));
#else
		node->GetPropVal(_T("Id"),&idval);
#endif
		while (node && (node->GetName() != sanitized_name || idval != idstr)) {
			old_node = node;
			node = node->GetNext();
			if (node) {
#if wxCHECK_VERSION(2,9,0)
				idval = node->GetAttribute(_T("Id"),_T(""));
#else
				node->GetPropVal(_T("Id"),&idval);
#endif
			}
		}
		if (!node && create_tree) {
			node = new node_type(wxXML_ELEMENT_NODE,sanitized_name);
			if (!old_node) {
				node_type * tmp = GetRoot();
				if (!tmp) {
					delete node;
					return;
				}
				old_node = tmp;
				tmp = tmp->GetChildren();
				if (!tmp) {
					old_node->SetChildren(tmp);
				} else {
					while (tmp) {
						old_node = tmp;
						tmp = tmp->GetNext();
					}
				}
			} else {
				old_node->SetNext(node);
			}
			current_node = node;
			Write("Id",id);
		} else current_node = node;
		if (node)
			states.push(state(node,sanitized_name));

		DEBUGLOG(config,_T("current path = '%s'"),
			 GetPath().c_str());
	}

	int xmltree::toFirstLeaf(const mutStringRef name,
				 mutStringRef id)
	{
		wxString sanitized_name = name;
		NormalizeName(sanitized_name);
		DEBUGLOG(config,_T("going to first leaf of group '%s'"),name.c_str());
		toLeaf(sanitized_name);
		if (current_node) {
#if wxCHECK_VERSION(2,9,0)
			id = current_node->GetAttribute(_T("Id"),_T(""));
#else
			current_node->GetPropVal(_T("Id"),&id);
#endif
		} else
			id = _T("0");

		return 0; // we don't use Ids.
	}


	int xmltree::toNextLeaf(const mutStringRef name, mutStringRef id)
	{
		wxString sanitized_name = name;
		NormalizeName(sanitized_name);
		node_type * node = current_node;
		if (!current_node) {
			id = _T("0");
			return wxNOT_FOUND;
		}
		do {
			node = node -> GetNext();
		} while (node && node->GetName() != sanitized_name);
		current_node = node;
		if (!node) {
			id = _T("0");
			return wxNOT_FOUND;
		}

		state & mystate = states.top();
		mystate.node = node;

#if wxCHECK_VERSION(2,9,0)
		id = node->GetAttribute(_T("Id"),_T(""));
#else
		node->GetPropVal(_T("Id"),&id);
#endif
		return 0;
	}


	void xmltree::toParent(unsigned int count)
	{
		DEBUGLOG(config,_T("going up %d level groups"),count);
		while (count--) {
#ifdef DEBUG
			mutASSERT(states.size());
#endif
			// we always keep the root element in the stack
			if (!(states.size()>=3)) {
				UNREACHABLEC;
				return;
			}
			states.pop();
			state & state = states.top();
			current_node = state.node;
		}
	}

	mutString xmltree::GetPath()
	{
		node_type * node = current_node;
		if (!node) return "/";
		wxString path = "/" + node->GetName();
		while ((node = node->GetParent()))
			wxString path = "/" + node->GetName() + path;
		return path;
	}

	void xmltree::SetPath(const mutStringRef path)
	{

		/* Warning!!!
		   This function as well as the inner loop have several exit points.
		   The loop step is done using goto.
		*/
		bool create = create_tree;
		if (!path) return;
		wxStringTokenizer tokenizer(path,"/");
		if (!tokenizer.HasMoreTokens()) return;
		wxString name = tokenizer.GetNextToken();
		node_type * node;
		if (!name) {
			if (!tokenizer.HasMoreTokens()) {
				current_node = NULL;
				return;
			}
			name = tokenizer.GetNextToken();
			node = GetRoot();
			if (!node) {
				if (!create) {
					current_node = NULL;
					return;
				}
				node = new node_type(current_node,
						     wxXML_ELEMENT_NODE,
						     name);
				SetRoot(node);
			} else if (node->GetName() != name) {
				current_node = NULL;
				return;
			}
			current_node = node;
			name = _T(".");
		} else if (!GetRoot() || !current_node) return;
		bool cont = false;
		do {
			node_type * last_node;
			cont = tokenizer.HasMoreTokens();
			if (!name || name == _T(".")) {
				goto loop_step;
			}
			if (!current_node) {
				if (GetRoot()->GetName() == name) {
					current_node = GetRoot();
					goto loop_step;
				}
				return;
			}
			if (name == _T("..")) {
				if (current_node == GetRoot()) {
					current_node = NULL;
					return;
				}
				current_node = current_node->GetParent();
				goto loop_step;
			}
			node = current_node->GetChildren();
			last_node = node;
			while (node && node -> GetName() != name) {
				last_node = node;
				node = node->GetNext();
			}
			if (!node) {
				if (!create) {
					current_node = NULL;
					return;
				}
				node = new node_type(current_node,
						     wxXML_ELEMENT_NODE,
						     name);
			}

			current_node = node;
		loop_step:
			if (cont) {
				name = tokenizer.GetNextToken();
			}
		} while (cont);
		return;
	}

	void xmltree::DeleteEntry(const mutStringRef path) {
		if (!current_node) return;
#if wxCHECK_VERSION(2,9,0)
		wxXmlAttribute * prop =
			current_node -> GetAttributes();
		wxXmlAttribute * last_prop = prop;
#else
		wxXmlProperty * prop =
			current_node->GetProperties();
		wxXmlProperty * last_prop = prop;
#endif
		while (prop && prop->GetName() != path) {
			last_prop = prop;
			prop = prop->GetNext();
		}
		if (!prop) {
			wxXmlNode * node = current_node;
			SetPath(path);
			if (current_node) {
				wxXmlNodeType type = current_node->GetType();
				switch (type) {
				case wxXML_ELEMENT_NODE:
				case wxXML_ATTRIBUTE_NODE:
				case wxXML_ENTITY_REF_NODE:
				case wxXML_ENTITY_NODE:
				case wxXML_PI_NODE:
				case wxXML_COMMENT_NODE:
				case wxXML_DOCUMENT_NODE:
				case wxXML_DOCUMENT_TYPE_NODE:
				case wxXML_DOCUMENT_FRAG_NODE:
				case wxXML_NOTATION_NODE:
				case wxXML_HTML_DOCUMENT_NODE:
					break;
				case wxXML_TEXT_NODE:
				case wxXML_CDATA_SECTION_NODE:
					delete current_node;
				}
			}
			current_node = node;
		}
		if (last_prop != prop) {
			last_prop->SetNext(prop->GetNext());
			prop->SetNext(NULL);
		} else {
#if wxCHECK_VERSION(2,9,0)
			current_node->SetAttributes(prop->GetNext());
#else
			current_node->SetProperties(prop->GetNext());
#endif
		}
			delete prop;
	}

	void xmltree::DeleteGroup(const mutStringRef path) {
		wxXmlNode * node = current_node;
		bool create = create_tree;
		create_tree = false;
		SetPath(path);
		if (current_node) {
			delete current_node;
		}
		create_tree = create;
		current_node = node;
	}

	wxXmlProperty * xmltree::GetProperty (mutString name,
					      bool create)
	{
		NormalizeName(name);
		if (!current_node) return NULL;
#if wxCHECK_VERSION(2,9,0)
		wxXmlAttribute * prop =
			current_node -> GetAttributes();
#else
		wxXmlProperty * prop =
			current_node->GetProperties();
#endif
		wxXmlProperty * last_prop = prop;
		while (prop && prop->GetName() != name) {
			last_prop = prop;
			prop = prop->GetNext();
		}
		if (!prop && create) {
			prop = new wxXmlProperty(name,"");
			if (last_prop) {
				last_prop->SetNext(prop);
			} else {
#if wxCHECK_VERSION(2,9,0)
				current_node->SetAttributes(prop);
#else
				current_node->SetProperties(prop);
#endif
			}
		}
		return prop;
	}
	wxXmlProperty * xmltree::SetProperty (mutString name,
					      mutStringRef value)
	{
		NormalizeName(name);
		if (!current_node) return NULL;
#if wxCHECK_VERSION(2,9,0)
		wxXmlAttribute * prop =
			current_node -> GetAttributes();
#else
		wxXmlProperty * prop =
			current_node->GetProperties();
#endif
		wxXmlProperty * last_prop = prop;
		while (prop && prop->GetName() != name) {
			last_prop = prop;
			prop = prop->GetNext();
		}
		if (!prop) {
			prop = new wxXmlProperty(name,value);
			if (last_prop) {
				last_prop->SetNext(prop);
			} else {
#if wxCHECK_VERSION(2,9,0)
				current_node->SetAttributes(prop);
#else
				current_node->SetProperties(prop);
#endif
			}
		} else {
			prop->SetValue(value);
		}
		return prop;
	}


	void xmltree::NormalizeName(mutStringRef name) {
		name.Replace(_T(" "),_T("-"));
	}
}

///\}
