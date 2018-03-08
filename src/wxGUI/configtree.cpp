/** \file
 ***********************************************************************
 * Class for tree like storage using wxFileConfig.
 *
 * \author T. Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/wxGUI/configtree.h"


long configtree::Read(const std::string& key, long defval)
{
	return config -> Read(key, defval);
}

double configtree::Read(const std::string& key, double defval)
{
	return config -> Read(key, defval);
}

int configtree::Read(const std::string& key, int defval)
{
	return (int) config -> Read(key, (long) defval);
}

bool configtree::Read(const std::string& key, bool defval)
{ 
	return (config -> Read(key, (long) defval) != 0L);
}

std::string configtree::Read(const std::string& key, const std::string& defval)
{
	wxString tmp = config -> Read(key, defval);
	return (const char *)(tmp.ToUTF8());
}
	
void configtree::Write (const std::string& key, long value)
{
	config -> Write(key, value);
}

void configtree::Write (const std::string& key, double value)
{
	config -> Write (key, value);
}

void configtree::Write (const std::string& key, int value)
{
	config -> Write (key, (long) value);
}

void configtree::Write (const std::string& key, bool value)
{
	config -> Write(key, (long) value);
}

void configtree::Write (const std::string& key, const std::string& value)
{	
	config -> Write (wxString::FromUTF8(key.c_str()), wxString::FromUTF8(value.c_str()));
}

bool configtree::HasGroup(const std::string& subdir) const
{
	return config->HasGroup(subdir);
}

void configtree::toLeaf(const std::string& subdir)
{
	DEBUGLOG (config, "going to group '%s'" ,subdir.c_str());
	mutASSERT(subdir.find('/') == std::string::npos);
	mutASSERT(subdir != "..");
	if (subdir.find('/') != std::string::npos || subdir == "..") {
		UNREACHABLEC;
		return;
	}
	state newstate;
#ifdef DEBUG
	newstate.oldpath = config -> GetPath();
#endif
	DEBUGLOG (config, "setting path to '%s'" ,(subdir).c_str());
	config -> SetPath(subdir);
	newstate.chdepth = 1;
	states.push(newstate);
	DEBUGLOG (config, "current path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')" ,
		 config->GetPath().c_str(), newstate.oldpath.c_str(), newstate.chdepth, 
		 newstate.leafid, newstate.group.c_str());
}

void configtree::toLeaf(const std::string& name, int id)
{
	DEBUGLOG (config, "going to group '%s' with id %d" ,name.c_str(),id);
	toLeaf(name);
	state newstate = states.top();
	config->SetPath(wxString::Format(_T("%d"),id));
	newstate.chdepth++;
	states.pop();
	states.push(newstate);
	DEBUGLOG (config, "current path = '%s',nowstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s'" ,
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, 
		 newstate.leafid, 
		 newstate.group.c_str());
}

int configtree::toFirstLeaf(const std::string& name,std::string& id) 
{
	DEBUGLOG (config, "going to first leaf of group '%s'" ,name.c_str());
	toLeaf(name);
	state & newstate = states.top();
	long int leafid;
	wxString ConfigId;
	bool found = config->GetFirstGroup(ConfigId,leafid);
	if (!found) {
		id = "0";
		newstate.leafid =  wxNOT_FOUND;
	} else {
		id = ConfigId.ToStdString();
		newstate.leafid = leafid;
	}		

	config->SetPath(id);
	newstate.chdepth++;
#ifdef DEBUG
	newstate.group=name;
	mutASSERT(newstate == states.top());
	DEBUGLOG(config,
		 ("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, 
		 newstate.leafid, 
		 newstate.group.c_str());
#endif
	return newstate.leafid;
}


int configtree::toNextLeaf(const std::string& name,
			   std::string& id)
{
	mutUnused(name);
#ifdef DEBUG
	DEBUGLOG (config, "going to next leaf of group '%s'" ,name.c_str());
	state oldstate=states.top();
	mutASSERT(oldstate.group==name);
	DEBUGLOG(config,
		 ("path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 oldstate.oldpath.c_str(), oldstate.chdepth, 
		 oldstate.leafid, oldstate.group.c_str());
#endif
	state & newstate = states.top();
	mutASSERT(newstate.leafid != wxNOT_FOUND);
	if (newstate.leafid == wxNOT_FOUND) 
		return wxNOT_FOUND;

	config -> SetPath(_T(".."));
	wxString ConfigId;
	bool found = config->GetNextGroup(ConfigId, newstate.leafid);
	if (found) {
		config->SetPath(ConfigId);
		id = ConfigId.ToStdString();
#ifdef DEBUG
		DEBUGLOG (config, "New leaf id = %ld" ,newstate.leafid);
		mutASSERT(oldstate.oldpath == newstate.oldpath);
#endif
	} else {
		newstate.chdepth--;
	}
	mutASSERT(newstate == states.top());
	DEBUGLOG(config,
		 ("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, newstate.leafid,
		 newstate.group.c_str());
	return newstate.leafid;
}


void configtree::toParent(unsigned int count)
{
	DEBUGLOG (config, "going up %d level groups" ,count);
	while (count--) {
#ifdef DEBUG
		mutASSERT(states.size());
#endif
		if (!states.size()) {
			UNREACHABLEC;
			return;
		}
		state oldstate = states.top();
		DEBUGLOG (config, "going up for %d levels" ,oldstate.chdepth);
		mutASSERT(oldstate.chdepth >= 0);
		if (oldstate.chdepth) {
			wxString setpath = _T("..");
			while (--(oldstate.chdepth))
				setpath << _T("/..");
			config -> SetPath(setpath);
		}
		states.pop();
#ifdef DEBUG
		mutASSERT(config->GetPath() == oldstate.oldpath);
#endif
		DEBUGLOG(config,
			 ("current path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
			 config->GetPath().c_str(), 
			 oldstate.oldpath.c_str(), 
			 oldstate.chdepth, oldstate.leafid, 
			 oldstate.group.c_str());
	}
} 

std::string configtree::GetPath()
{
	return (const char *)(config -> GetPath().ToUTF8());
}

void configtree::SetPath(const std::string& path)
{
	DEBUGLOG (config, "setting path directly to '%s'" ,path.c_str());
	config->SetPath(path);
}




///\}
