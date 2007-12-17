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

mutString CurrentLine;//[GSP_MAX_LINE];
int  CurrentPos;
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
int OpenFile(const mutString Name)
{
//  File = new STD_PRE::ifstream(Name, STD_PRE::ios::in/*, 0/*int = filebuf::openprot*/);
  File = new mutOpenITextStream(,Name);
  initialized = false;
#ifdef WX
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
  if ( (Eof = mutStreamEOF(*File)) || bad )
  {
	 CurrentLine[0] = 0;
	 return bad;
  }
  if (initialized)
	CurrentLine = File->GetNextLine();
  else {
    CurrentLine = File->GetFirstLine();
  }
  GspCurrentLineNr++;
  return bad;
#else
  if ( (Eof = mutStreamEOF(*File)) || mutStreamBad(*File) )
  {
	 CurrentLine[0] = 0;
	 return mutStreamBad(*File);
  }
  File->getline(CurrentLine, GSP_MAX_LINE);
  GspCurrentLineNr++;
  return mutStreamBad(*File);
#endif
}

