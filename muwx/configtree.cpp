/** \file
 ***********************************************************************
 * abstract class for tree like storage
 *
 * $Id: configtree.cpp,v 1.4 2010/12/11 02:10:09 keinstein Exp $
 * \author T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2010/12/11 02:10:09 $
 * \version $Revision: 1.4 $
 *
 * $Log: configtree.cpp,v $
 * Revision 1.4  2010/12/11 02:10:09  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.3  2010-11-21 23:39:00  keinstein
 * some corrections for allowing debuild to complete
 *
 * Revision 1.2  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-09-29 13:03:30  keinstein
 * config can be stored and restored with new treeconfig
 *
 * Revision 1.1.2.2  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.1.2.1  2010-08-10 16:33:37  keinstein
 * added simple wrapper for config and XML like files
 *
 *
 *
 */
#include "Defs.h"
#include "configtree.h"


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
	return config -> Read(key, (long) defval);
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
	wxASSERT(subdir.Find('/') == wxNOT_FOUND);
	wxASSERT(subdir != _T(".."));
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
	DEBUGLOG(config,_T("current path = '%s', old path = '%s', depth = %d, id = %d, name = '%s'"),
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
	DEBUGLOG(config,_T("current path = '%s', old path = '%s', depth = %d, id = %d, name = '%s'"),
		 config->GetPath().c_str(), newstate.oldpath.c_str(), newstate.chdepth, 
		 newstate.leafid, newstate.group.c_str());
}

int configtree::toFirstLeaf(const mutStringRef name,mutStringRef id) 
{
	DEBUGLOG(config,_T("going to first leaf of group '%s'"),name.c_str());
	toLeaf(name);
	state newstate = states.top();
	bool found = config->GetFirstGroup(id,newstate.leafid);
	if (!found) {
		id = _T("0");
		newstate.leafid = wxNOT_FOUND;
	}
	config->SetPath(id);
	newstate.chdepth++;
#ifdef DEBUG
	newstate.group=name;
#endif
	states.pop();
	states.push(newstate);
	DEBUGLOG(config,
		 _T("current path = '%s', old path = '%s', depth = %d, id = %d, name = '%s'"),
		 config->GetPath().c_str(), newstate.oldpath.c_str(), newstate.chdepth, 
		 newstate.leafid, newstate.group.c_str());
	return newstate.leafid;
}


int configtree::toNextLeaf(const mutStringRef name, mutStringRef id)
{
#ifdef DEBUG
	DEBUGLOG(config,_T("going to next leaf of group '%s'"),name.c_str());
	state oldstate=states.top();
	wxASSERT(oldstate.group==name);
	DEBUGLOG(config,
		 _T("current path = '%s', old path = '%s', depth = %d, id = %d, name = '%s'"),
		 config->GetPath().c_str(), 
		 oldstate.oldpath.c_str(), oldstate.chdepth, 
		 oldstate.leafid, oldstate.group.c_str());
#endif
	toParent(1);
	toLeaf(name);
	state newstate = states.top();
#ifdef DEBUG
	DEBUGLOG(config,
		 _T("current path = '%s', new old path = '%s', depth = %d, id = %d, name = '%s'"),
		 config->GetPath().c_str(), 
		 newstate.oldpath.c_str(), 
		 newstate.chdepth, newstate.leafid, newstate.group.c_str());
	wxASSERT(oldstate.oldpath == newstate.oldpath);
	newstate.group = oldstate.group;
#endif
	bool found = config->GetNextGroup(id, newstate.leafid);
	if (found) {
		config->SetPath(id);
		newstate.chdepth++;
	} else newstate.leafid=wxNOT_FOUND;
	states.pop();
	states.push(newstate);
	DEBUGLOG(config,
		 _T("current path = '%s', new old path = '%s', depth = %d, id = %d, name = '%s'"),
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
		wxASSERT(states.size());
#endif
		if (!states.size()) {
			UNREACHABLEC;
			return;
		}
		state oldstate = states.top();
		DEBUGLOG(config,_T("going up for %d levels"),oldstate.chdepth);
		while (oldstate.chdepth--) 
			config -> SetPath(_T(".."));
		states.pop();
#ifdef DEBUG
		wxASSERT(config->GetPath() == oldstate.oldpath);
#endif
		DEBUGLOG(config,
			 _T("current path = '%s', old path = '%s', depth = %d, id = %d, name = '%s'"),
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


