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
#if (!defined(MUWX_CONFIGTREE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_CONFIGTREE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_CONFIGTREE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Box.h"
#include "src/kernel/treestorage.h"

#ifndef MUWX_CONFIGTREE_H_PRECOMPILED
#define MUWX_CONFIGTREE_H_PRECOMPILED

#include <stack>

class configtree:public mutabor::tree_storage 
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
	mutabor::BoxFactory::LoadBoxes(conf);
	mutabor::RouteFactory::LoadRoutes(conf);
}

inline void SaveRoutes(wxConfigBase * config)
{
	configtree conf(config);
	mutabor::BoxFactory::SaveBoxes(conf);
	mutabor::RouteFactory::SaveRoutes(conf);
}

#endif //MUTABOR_CONFIGTREE_H_PRECOMPILED
#endif //MUTABOR_CONFIGTREE_H


///\}
