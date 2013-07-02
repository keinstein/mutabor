/** \file
 ***********************************************************************
 * abstract class for tree like storage
 *
 * $Id: configtree.cpp,v 1.8 2011/11/02 14:31:59 keinstein Exp $
 * \author T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.8 $
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


long configtree::Read(const mutStringRef key, long defval)
{
	return config -> Read(key, defval);
}

double configtree::Read(const mutStringRef key, double defval)
{
	return config -> Read(key, defval);
}

int configtree::Read(const mutStringRef key, int defval)
{
	return (int) config -> Read(key, (long) defval);
}

bool configtree::Read(const mutStringRef key, bool defval)
{ 
	return (config -> Read(key, (long) defval) != 0L);
}

mutString configtree::Read(const mutStringRef key, const mutStringRef defval)
{
	return config -> Read(key, defval);
}
	
void configtree::Write (const mutStringRef key, long value)
{
	config -> Write(key, value);
}

void configtree::Write (const mutStringRef key, double value)
{
	config -> Write (key, value);
}

void configtree::Write (const mutStringRef key, int value)
{
	config -> Write (key, (long) value);
}

void configtree::Write (const mutStringRef key, bool value)
{
	config -> Write(key, (long) value);
}

void configtree::Write (const mutStringRef key, const mutStringRef value)
{	
	config -> Write (key, value);
}

bool configtree::HasGroup(const mutStringRef subdir) const
{
	return config->HasGroup(subdir);
}

void configtree::toLeaf(const mutStringRef subdir)
{
	DEBUGLOG(config,_T("going to group '%s'"),subdir.c_str());
	mutASSERT(subdir.Find('/') == wxNOT_FOUND);
	mutASSERT(subdir != _T(".."));
	if (subdir.Find('/') != wxNOT_FOUND || subdir == _T("..")) {
		UNREACHABLEC;
		return;
	}
	state newstate;
#ifdef DEBUG
	newstate.oldpath = config -> GetPath();
#endif
	DEBUGLOG(config,_T("setting path to '%s'"),(subdir).c_str());
	config -> SetPath(subdir);
	newstate.chdepth = 1;
	states.push(newstate);
	DEBUGLOG(config,_T("current path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), newstate.oldpath.c_str(), newstate.chdepth, 
		 newstate.leafid, newstate.group.c_str());
}

void configtree::toLeaf(const mutStringRef name, int id)
{
	DEBUGLOG(config,_T("going to group '%s' with id %d"),name.c_str(),id);
	toLeaf(name);
	state newstate = states.top();
	config->SetPath(wxString::Format(_T("%d"),id));
	newstate.chdepth++;
	states.pop();
	states.push(newstate);
	DEBUGLOG(config,_T("current path = '%s',nowstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s'"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, 
		 newstate.leafid, 
		 newstate.group.c_str());
}

int configtree::toFirstLeaf(const mutStringRef name,mutStringRef id) 
{
	DEBUGLOG(config,_T("going to first leaf of group '%s'"),name.c_str());
	toLeaf(name);
	state & newstate = states.top();
	long int leafid;
	bool found = config->GetFirstGroup(id,leafid);
	if (!found) {
		id = _T("0");
		newstate.leafid =  wxNOT_FOUND;
	} else {
		newstate.leafid = leafid;
	}		

	config->SetPath(id);
	newstate.chdepth++;
#ifdef DEBUG
	newstate.group=name;
	mutASSERT(newstate == states.top());
	DEBUGLOG(config,
		 _T("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, 
		 newstate.leafid, 
		 newstate.group.c_str());
#endif
	return newstate.leafid;
}


int configtree::toNextLeaf(const mutStringRef name, mutStringRef id)
{
#ifdef DEBUG
	DEBUGLOG(config,_T("going to next leaf of group '%s'"),name.c_str());
	state oldstate=states.top();
	mutASSERT(oldstate.group==name);
	DEBUGLOG(config,
		 _T("path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 oldstate.oldpath.c_str(), oldstate.chdepth, 
		 oldstate.leafid, oldstate.group.c_str());
#endif
	state & newstate = states.top();
	mutASSERT(newstate.leafid != wxNOT_FOUND);
	if (newstate.leafid == wxNOT_FOUND) 
		return wxNOT_FOUND;

	config -> SetPath(_T(".."));
	bool found = config->GetNextGroup(id, newstate.leafid);
	if (found) {
		config->SetPath(id);
#ifdef DEBUG
		DEBUGLOG(config,_T("New leaf id = %ld"),newstate.leafid);
		mutASSERT(oldstate.oldpath == newstate.oldpath);
#endif
	} else {
		newstate.chdepth--;
	}
	mutASSERT(newstate == states.top());
	DEBUGLOG(config,
		 _T("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, newstate.leafid,
		 newstate.group.c_str());
	return newstate.leafid;
}


void configtree::toParent(unsigned int count)
{
	DEBUGLOG(config,_T("going up %d level groups"),count);
	while (count--) {
#ifdef DEBUG
		mutASSERT(states.size());
#endif
		if (!states.size()) {
			UNREACHABLEC;
			return;
		}
		state oldstate = states.top();
		DEBUGLOG(config,_T("going up for %d levels"),oldstate.chdepth);
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
			 _T("current path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %ld, group = '%s')"),
			 config->GetPath().c_str(), 
			 oldstate.oldpath.c_str(), 
			 oldstate.chdepth, oldstate.leafid, 
			 oldstate.group.c_str());
	}
} 

mutString configtree::GetPath()
{
	return config -> GetPath();
}

void configtree::SetPath(const mutStringRef path)
{
	DEBUGLOG(config,_T("setting path directly to '%s'"),path.c_str());
	config->SetPath(path);
}




///\}
