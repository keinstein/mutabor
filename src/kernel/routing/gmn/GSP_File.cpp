/** \file
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/gmn/GSP_File.cpp,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: GSP_File.cpp,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// file input of gsp (GMN Soft Parser)
// Has to be adapted depending on platform.
// This is for PC.
// ##################################################################

#include "GSP_File.h"

#include <fstream>
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/detail/utf8_codecvt_facet.hpp"

std::string CurrentLine;//[GSP_MAX_LINE];
size_t  CurrentPos;
int  Eof;

boost::filesystem::ifstream * File;  // the file

#ifdef WX
static int bad = 0;
#endif

// ##################################################################
// basic file operations
// Return values that are not 0 means, that an error occured.
// A call back implemented in ReadNewLine may be used for displaying
// the current line number.

// opens the file
int OpenFile(const std::string &Name)
{
	/* tell boost that we are using UTF-8 file names */
	boost::filesystem::detail::utf8_codecvt_facet utf8;
	boost::filesystem::path p;
	p.assign(Name, utf8);

//  File = new STD_PRE::ifstream(Name, STD_PRE::ios::in/*, 0/*int = filebuf::openprot*/);
	File = new boost::filesystem::ifstream(p, std::ios::in);
	if (!File ) return -1;
	if (!File->is_open()) return -2;
	if (File->bad()) return -3;
	if (File->fail()) return -4;
	return 0;
#if 0
	initialized = false;
	return bad=(!(File->Open()));
	return mutStreamBad(*File);
#endif
}

// closes the file
int CloseFile()
{
	delete File;
	return 0;
}


// reads a line into CurrentLine
int ReadNewLine()
{
	CurrentPos = 0;
	if (!File) return -1;

	if ( (Eof = File->eof()) || (bad = File->bad()) ) {
		CurrentLine  = "";
		return bad;
	}

	std::getline(*File, CurrentLine);

	GspCurrentLineNr++;

	return bad = File->bad();
#if 0

	if ( (Eof = mutStreamEOF(*File)) || mutStreamBad(*File) ) {
		CurrentLine[0] = 0;
		return mutStreamBad(*File);
	}

	File->getline(CurrentLine, GSP_MAX_LINE);

	GspCurrentLineNr++;
	return mutStreamBad(*File);
#endif
}



///\}
