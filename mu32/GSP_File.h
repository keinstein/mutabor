// ##################################################################
// file input of gsp (GMN Soft Parser)
// ##################################################################

#ifndef GSP_FILE_H
#define GSP_FILE_H

#include "GSP.h"

extern char CurrentLine[GSP_MAX_LINE];
extern int  CurrentPos;
extern int  Eof;

int OpenFile(const char *Name);
int CloseFile();
int ReadNewLine();

#endif

