/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GSP_File.cpp,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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

#ifdef WX
#include "wx/textfile.h"
#else
#include <fstream>
#endif

#ifdef WX
mutString CurrentLine;//[GSP_MAX_LINE];
#else
mutChar CurrentLine[GSP_MAX_LINE];
#endif
size_t  CurrentPos;
int  Eof;

mutTextStream* File;  // the file

#ifdef WX

static bool initialized = false;

static int bad = 0;

#endif

// ##################################################################
// basic file operations
// Return values that are not 0 means, that an error occured.
// A call back implemented in ReadNewLine may be used for displaying
// the current line number.

// opens the file
int OpenFile(const mutString &Name)
{
//  File = new STD_PRE::ifstream(Name, STD_PRE::ios::in/*, 0/*int = filebuf::openprot*/);
	File = new mutOpenITextStream(,Name);
#ifdef WX
	initialized = false;
	return bad=(!(File->Open()));
#else
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
#ifdef WX

	if ( (Eof = mutStreamEOF(*File)) || bad ) {
		CurrentLine  = mutEmptyString;
		return bad;
	}

	if (initialized)
		CurrentLine = File->GetNextLine();
	else {
		CurrentLine = File->GetFirstLine();
		initialized = true;
	}

	GspCurrentLineNr++;

	return bad;
#else

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
