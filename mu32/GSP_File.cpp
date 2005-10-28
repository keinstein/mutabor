// ##################################################################
// file input of gsp (GMN Soft Parser)
// Has to be adapted depending on platform.
// This is for PC.
// ##################################################################

#include "GSP_File.h"
#include <fstream>

char CurrentLine[GSP_MAX_LINE];
int  CurrentPos;
int  Eof;

STD_PRE::ifstream *File;  // the file

// ##################################################################
// basic file operations
// Return values that are not 0 means, that an error occured.
// A call back implemented in ReadNewLine may be used for displaying
// the current line number.

// opens the file
int OpenFile(const char *Name)
{
  File = new STD_PRE::ifstream(Name, STD_PRE::ios::in/*, 0/*int = filebuf::openprot*/);
  return File->bad();
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
  if ( File->eof() || File->bad() )
  {
	 Eof = File->eof();
	 CurrentLine[0] = 0;
	 return File->bad();
  }
  File->getline(CurrentLine, GSP_MAX_LINE);
  GspCurrentLineNr++;
  return File->bad();
}

