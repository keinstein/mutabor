// ##################################################################
// header file of gsp (GMN Soft Parser)
// ##################################################################

#ifndef GSP_H
#define GSP_H

#include "Frac.h"

// #define GMN_STRICT

#define GSP_MAX_SEP 8000  // maximal length of a comment
#define GSP_MAX_LINE 1000  // maximal length of a line

extern int GspCurrentLineNr;    // curent line parser deals with
extern int GspErrorLineNr;      // line of occured error
extern int GspErrorPos;         // column of occured error in line
extern mutString GspErrorLine;      // text of error line
extern int  GspError;           // error id

#ifdef WX
  extern mutString Sep;
#else
  extern char[GSP_MAX_SEP];
#endif
extern int  SepPos;

extern char *GspErrorText[];

int GspParse(const mutString FileName);

// extern user defined functions

extern int StartSep();  // at the beginning, to get comments infront of the first token
extern int BeginSegment();
extern int EndSegment();
extern int BeginSequenz();
extern int EndSequenz();
extern int BeginParameter();
extern int EndParameter();
extern int BeginRange();
extern int EndRange();
extern int NextSequenz();
extern int Note(mutString name, mutString accedentials, int octave,
  frac duration);
extern int Tag(mutString tagName);
extern int TagParaInt(long i);
extern int TagParaReal(double x);
extern int TagParaStr(mutString s);
extern int Comma();

#endif

