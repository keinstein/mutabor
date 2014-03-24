/** \file 
 ********************************************************************
 * Main debugging functions
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
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
 * \defgroup debug Debugging functions 
 *
 * This group contains the functions that are used to help debugging
 * of Mutabor. Despite the core is written in C these functions are
 * written in C++ but can easily replaced by C.
 * 
 * \{
 ********************************************************************/
/*
 *  mutDebug.h
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

#ifndef __MUTDEBUGFLAGS__
#define __MUTDEBUGFLAGS__

#ifdef DEBUG


#include <bitset>
#include <iostream>
#include <cstdio>
#include <vector>
#include <stdint.h>
#include "wx/cmdline.h"
#include "wx/string.h"
#include "wx/debug.h"
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#ifdef WX
#include "wx/thread.h"
//typedef wxMutex debugMutex;
//typedef wxMutexLocker debugScopedLock;
#else 
#error this file should be included only in wxWidgets related source code files;
#endif



void InitDebugCommandLine(wxCmdLineParser&  parser);
void ProcessDebugCommandLine(wxCmdLineParser&  parser);




//extern debugMutex debugmutex;

#endif
#endif

///\}
