// ##################################################################
// GUIDO-MUTABOR
// command line converter
// *.gmn to *.gmn via *.mut
// ##################################################################

//#include <iostream.h>
//#include <iostream>
//#include <fstream.h>
#include <fstream>
//#include <setjmp.h>
//#include <string.h>

//#include "gsp.h"
//#include "gis.h"
#include "gis_head.h"
//#include "global.h"
#include "hilfs.h"
#include "grafkern.h"
///#include "midikern.h"
#include "execute.h"

#include "ext.h"
#include "device.h"

ostream *Echo = &cout;

jmp_buf weiter_gehts_nach_compilerfehler;

typedef struct INLISTTAG
{
  INLISTTAG *Next;
  GisToken *Data;
  InDevice *Device;
  char *Name;
} InListTag;

typedef struct OUTLISTTAG
{
  OUTLISTTAG *Next;
  OutGis *Device;
  char *Name;
} OutListTag;

InListTag *InList = 0;
OutListTag *OutList = 0;

#define OUTLISTDATA Out->Device->Head->Data

int Error = 0;

// command line parsing ---------------------------------------------

InDevice *GetInFile(char *name)
{
  char *Name = ExtCheck(name, "gmn");
  for ( InListTag *In = InList; In; In = In->Next)
	 if ( !strcmp(Name, In->Name) )
		return In->Device;
  *Echo << "GSP parsing file: " << Name << " ...";
  GisToken *Data = GisParse(Name);
  if ( GspError )
  {
	 *Echo << "\n  Parsing interupted !\n";
	 *Echo << "  ErrorNr: " << GspError << " - " << GspErrorText[GspError] << "\n";
	 *Echo << "  Line: " << GspErrorLineNr << ", " << GspErrorPos << "\n";
	 *Echo << "  " << GspErrorLine << "\n  ";
	 for (int i = 0; i < GspErrorPos; i++) *Echo << " ";
	 *Echo << "^";
	 Error = 1;
	 return 0;
  }
  else
	 *Echo << " OK\n";
  In = new InListTag();
  In->Next = InList;
  InList = In;
  In->Data = Data;
  In->Device = new InGis(Data, name);
  In->Name = strdup(Name);
  return In->Device;
}

OutDevice *GetOutFile(char *name)
{
  // check, wether no output
  if ( !name[0] )
	 return 0;
  // check, wether already listed
  char *Name = ExtCheck(name, "gmn");
  for ( OutListTag *Out = OutList; Out; Out = Out->Next)
	 if ( !strcmp(Name, Out->Name) )
		return Out->Device;
  // make new output device
  Out = new OutListTag();
  Out->Next = OutList;
  OutList = Out;
  Out->Device = new OutGis(""/*name*/);
  Out->Name = strdup(Name);
  return Out->Device;
}

void DoRoute(InDevice *In, OutDevice *Out, char *s)
{
  // get route type
  RouteType Type = RTall;
  char *s1 = s;
  switch ( s[0] )
  {
	 case 'a':
	 case 'A':
		Type = RTall;
		s1 = strchr(s, ',');
		break;
	 case 'e':
	 case 'E':
		Type = RTelse;
		s1 = strchr(s, ',');
		break;
	 case 's':
	 case 'S':
		Type = RTstaff;
		s1 = strchr(s, ',');
		break;
	 case 'c':
	 case 'C':
		Type = RTchannel;
		s1 = strchr(s, ',');
		break;
  }
  if ( s1[0] == ',' ) s1++;
  // get numbers
  int a, b, c;
  int n = sscanf(s1, "%i,%i,%i", &a, &b, &c);
  switch ( n )
  {
	 case 3:
		In->AddRoute(new Route(Type, a, b, c, Out));
		break;
	 case 2:
		In->AddRoute(new Route(Type, a, a, b, Out));
		break;
	 case 1:
		In->AddRoute(new Route(Type, 0, 0, a, Out));
		break;
	 default:
		In->AddRoute(new Route(Type, 0, 0, 0, Out));
  }
}

// compiler function ------------------------------------------------

char GMutCompile(char *fileName)
{

  if ( !setjmp(weiter_gehts_nach_compilerfehler) )
  {
	 loesche_syntax_speicher();
	 init_yylex ();

	 *Echo << "Mutabor parsing file: " << fileName << "\n";

	 mutabor_programm_einlesen ( fileName );

	 calc_declaration_numbers(1);

	 *Echo << sd1 << "\n";
	 *Echo << sd2 << "\n";

	 *Echo << "Generating tables\n";

	 mutabor_tabellen_generator();

	 *Echo << "Translation successful !\n";
	 *Echo << "No error occured !\n";

	 return 1;
  }
  else
  {
	 *Echo << "Translation interrupted !\n";
	 *Echo << "Error: " << Fmeldung;
	 return 0;
  }
}

void PrintHelp()
{
  *Echo << "for more information please visit:\n";
  *Echo << "  http://rcswww.urz.tu-dresden.de/~rkrausse/gmut.htm\n";
  *Echo << "Usage: gmut mutfile[.mut] route [route, route, ...] [options]\n";
  *Echo << "  mutfile\n";
  *Echo << "  	Mutabor file as used for Mutabor II, Extension .mut\n";
  *Echo << "  route\n";
  *Echo << "    Declares the way of data thru GMut:\n";
  *Echo << "      infile(type,from,to,box)outfile\n";
  *Echo << "    where:\n";
  *Echo << "      infile    name of a file in GUIDO Music Notation\n";
  *Echo << "      type      all, staff, box, else\n";
  *Echo << "      from, to  staff / box numbers\n";
  *Echo << "      box       box to proceed the data\n";
  *Echo << "      outfile   name of outpt file\n";
  *Echo << "    Write these all without blank.\n";
  *Echo << "  options:\n";
  *Echo << "    /key:nr,string   Sequenz of computer keys as input for instrument 0\n";
  *Echo << "                     (to force tonsystems instead of logics use leading \"&\")\n";
  *Echo << "    /silent          Convert with no echo at all\n";
  *Echo << "    /report          Report into file gmut.rep\n";
  *Echo << "    /help            Shows this help screen\n";
}

// ##################################################################

int main(int argc, char* argv [])
{
  // read mutabor file and output options
  char *MutFile = 0;
  char Help = 0;
  for (int i = 1; i < argc; i++)
	 if ( argv[i][0] == '-' || argv[i][0] == '/' ) // option
	 {
		strlwr(argv[i]);
		if ( !strcmp(&argv[i][1], "silent") )
		{
		  Echo = new ofstream("nul:");
		}
		else if ( !strcmp(&argv[i][1], "help") || !strcmp(&argv[i][1], "h") || !strcmp(&argv[i][1], "?"))
		  Help = 1;
		else if ( !strcmp(&argv[i][1], "report") )
		{
		  Echo = new ofstream("gmut.rep");
		}
	 }
	 else // parameter
	 {
		char *s1 = strchr(argv[i], '(');
		char *s2 = strchr(argv[i], ')');
		if ( s1 && s2 && s1 < s2 ) // route
		  continue;
		if ( !MutFile ) // Mutabor-file
		  MutFile = strdup(argv[i]);
	 }
  // info text
  *Echo << "GMut - GUIDO Mutabor converter, TU Dresden, R.K. 1998, Version 0.70\n";
  if ( Help )
	 PrintHelp();
  // scan complex parameters
  for (i = 1; i < argc; i++)
	 if ( argv[i][0] == '-' || argv[i][0] == '/' ) // option
		continue;
	 else // parameter
	 {
		char *s1 = strchr(argv[i], '(');
		char *s2 = strchr(argv[i], ')');
		if ( s1 && s2 && s1 < s2 ) // route
		{
		  s1[0] = 0; s1++;
		  s2[0] = 0; s2++;
		  InDevice *In = GetInFile(argv[i]);
		  if ( Error ) return 1;
		  OutDevice *Out = GetOutFile(s2);
		  if ( Error ) return 2;
		  DoRoute(In, Out, s1);
		}
	 }
  if ( !InList )  // to few parameters
  {
	 PrintHelp();
	 return 1;
  }
  // read *.mut file
  if ( !GMutCompile(ExtCheck(MutFile, "mut")) ) return 0;
  // translate via mutabor
  // init mutabor
  *Echo << "Translating ";
  // prepare output
  GlobalReset( );
  aktionen_init();
  // keyboard analysis
  for (i = 1; i < argc; i++)
	 if ( argv[i][0] == '-' || argv[i][0] == '/' ) // option
	 {
		strlwr(argv[i]);
		if ( !strncmp(&argv[i][1], "key:",3) )
		{
		  int Nr;
		  char s[80];
		  sscanf(&argv[i][5], "%i,%s", &Nr, &s);
		  if ( Nr >=0 )
			 KeyboardIn(Nr, s);
		}
	 }
  // open devices
  frac z = frac(0,1);
  InOpen();
  OutOpen();
  // main loop
  while ( z >= frac(0,1) )
  {
	 z = InReadOn(z);
	 if ( z > frac(0,1) )
		OutAddTime(z);
  }
  *Echo << "... OK\n";
  // close mutabor
  GlobalReset();
  // close devices
  InClose();
  OutClose();
  // save files
  for ( OutListTag *Out = OutList; Out; Out = Out->Next )
  {
	 *Echo << "Saving " << Out->Name << " ...";
	 if ( OUTLISTDATA )
	 {
		// add comment in outputfile
		if ( OUTLISTDATA->Type() != GTUnknown )
		{
		  OUTLISTDATA = new GisToken("", OUTLISTDATA);
		}
		char *s = OUTLISTDATA->Sep;
		char *s1 = (char*) malloc(strlen(s)+200);
		strcpy(s1, s);
		strcat(s1, "\n(* mutated by GMUT Version 0.70 via ");
		strcat(s1, MutFile);
	/*	 if ( KeyBoard[0] )
		{
		  strcat(s1, " Keys: \"");
		  strcat(s1, KeyBoard);
		  strcat(s1, "\"");
		} */
		strcat(s1, " *)\n");
		OUTLISTDATA->Sep = s1;
		free(s);
		// save file
		ofstream os = ofstream(Out->Name);
		OUTLISTDATA->Stream(os,1);
		os.flush();
	 }
	 *Echo << " OK\n";
  }
  Echo->flush();
  return 0;
}

