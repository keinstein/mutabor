/** \file  -*- C++ -*-
 ***********************************************************************
 * implementation class for tree like storage using wxConfigBase based 
 * classes.
 *
 * $Id: configtree.h,v 1.6 2011/09/27 20:13:24 keinstein Exp $
 * \author T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: configtree.h,v $
 * Revision 1.6  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-09 09:29:10  keinstein
 * fix loading of routing configuration
 *
 * Revision 1.4  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-09-29 15:06:40  keinstein
 * Reset config before saving routing information and fix two bugs concerned with the deletion of boxes
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
#if (!defined(MUWX_CONFIGTREE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_CONFIGTREE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_CONFIGTREE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Route.h"
#include "treestorage.h"

#ifndef MUWX_CONFIGTREE_H_PRECOMPILED
#define MUWX_CONFIGTREE_H_PRECOMPILED

#include <stack>

class configtree:public tree_storage 
{
	wxConfigBase * config; ///< configuration object
	bool deleteconfig; ///< true if the config is private and must be deleted on deletion
	
	/// structure describing the current state
	struct state {
		state() {
			chdepth = 0;
			leafid = wxNOT_FOUND;
		}
		int chdepth; ///< depth of last toLeaf... command
		long leafid; ///< id from wxWidgets for sequential access
#ifdef DEBUG
		wxString oldpath; ///< back up old path, so that we can check consistency
		wxString group;
#endif
		bool operator == (const state & s) const 
			{
				bool retval = chdepth == s.chdepth 
				&& leafid == s.leafid; 
#ifdef DEBUG
				retval = retval && oldpath == s.oldpath
				&& group == s.group;
#endif
				return retval;
			}
	};
	std::stack<state> states;
public:
	configtree(wxConfigBase * conf, bool ownconfig = false):config(conf),deleteconfig(ownconfig),states()
	{
	}
	
	virtual ~configtree() 
	{
		if (deleteconfig) delete config;
	}

	virtual long Read(const mutStringRef key, long defval);
	virtual double Read(const mutStringRef key, double defval);
	virtual int Read(const mutStringRef key, int defval);
	virtual bool Read(const mutStringRef key, bool defval);
	virtual mutString Read(const mutStringRef key, const mutStringRef defval);
	
	virtual void Write (const mutStringRef key, long value);
	virtual void Write (const mutStringRef key, double value);
	virtual void Write (const mutStringRef key, int value);
	virtual void Write(const mutStringRef key, bool value);
	virtual void Write (const mutStringRef key, const mutStringRef value);

	virtual bool HasGroup(const mutStringRef subdir) const;
	virtual void toLeaf(const mutStringRef subdir);
	virtual void toLeaf(const mutStringRef name, int id);
	virtual int toFirstLeaf(const mutStringRef name)
	{
		mutString id;
		if (toFirstLeaf(name,id) == wxNOT_FOUND) 
			return wxNOT_FOUND;
		long i;
		if (id.ToLong(&i)) return (int)i; 
		else return wxNOT_FOUND;
	}
	virtual int toFirstLeaf(const mutStringRef name, mutStringRef id);
	virtual int toNextLeaf(const mutStringRef name)
	{
		mutString id;
		if (toNextLeaf(name,id) == wxNOT_FOUND)
			return wxNOT_FOUND;
		long i;
		if (id.ToLong(&i)) return (int)i; 
		else return wxNOT_FOUND;		
	}
	virtual int toNextLeaf(const mutStringRef name, mutStringRef id);
	virtual void toParent(unsigned int count = 1);

	virtual mutString GetPath();
	virtual void SetPath(const mutStringRef path);
	
	/// Delete an entry
	/** 
	 *  \argument entry path to the entry that shall be deleted
	 */
	virtual void DeleteEntry(const mutStringRef path)
	{
		config->DeleteEntry(path);
	}
	
	/// Delete an entire group with all childs
	/** 
	 *  \argument group path to the entry that shall be deleted
	 */
	virtual void DeleteGroup(const mutStringRef path)
	{
		config->DeleteGroup(path);
	}
};

inline void LoadRoutes(wxConfigBase * config)
{
	configtree conf(config);
	mutabor::RouteFactory::LoadRoutes(conf);
}

inline void SaveRoutes(wxConfigBase * config)
{
	configtree conf(config);
	mutabor::RouteFactory::SaveRoutes(conf);
}

#endif //MUTABOR_CONFIGTREE_H_PRECOMPILED
#endif //MUTABOR_CONFIGTREE_H


///\}
