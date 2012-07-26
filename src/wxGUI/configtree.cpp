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
 * $Log: configtree.cpp,v $
 * Revision 1.8  2011/11/02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.6  2011-09-09 09:29:10  keinstein
 * fix loading of routing configuration
 *
 * Revision 1.5  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.4  2010-12-11 02:10:09  keinstein
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
	DEBUGLOG(config,_T("current path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s')"),
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
	DEBUGLOG(config,_T("current path = '%s',nowstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s'"),
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
		 _T("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s')"),
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
		 _T("path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s')"),
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
		 _T("path = '%s', newstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s')"),
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
			 _T("current path = '%s', oldstate(oldpath = '%s', chdepth = %d, leafid = %d, group = '%s')"),
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
