// ##################################################################
// GUIDO-MUTABOR
// command line converter
// *.gmn to *.gmn via *.mut
// ##################################################################

/*#include "gsp.h"
#include "gis.h"
#include "gis_head.h"*/
//#include <iostream.h>
#include <iostream>
//#include <fstream.h>
#include <fstream>
#include <setjmp.h>
#include <string.h>
//#include "mis.h"
#include "global.h"
#include "hilfs.h"
#include "grafkern.h"
#include "midikern.h"
#include "execute.h"

#include "ext.h"
/*#include "mutgis.h"
#include "device.h"
*/
//OutGis *Write;

std::ostream *Echo = &std::cout;

jmp_buf weiter_gehts_nach_compilerfehler;

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

///	 show_line_number(-1);

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

void KeyboardIn(int box, char *keys)
{
  aktuelles_keyboard_instrument = box;
  char TonSystem = 0;
  for (int i= 0; i < strlen(keys); i++)
  {
	 char c = keys[i];
	 if ( c == '&' )
	 {
		TonSystem = 1;
		continue;
	 }
	 if ( '0' <= c && c <= 'z' )
		if ( TonSystem )
		  keyboard_analyse((int) c, 0);
		else
		  keyboard_analyse((int) c);
	 TonSystem = 0;
  }
}
/*
void MutaborTag(GisReadArtHead *h, GisToken *Para)
{
  if ( !Para || Para->Type() != GTParaStr )
	 return; // strange parameters
  char *ParaName = ((GisParaStr*)Para)->s;
  Para = Para->Next;
  if ( !strcmp(ParaName, "key") )
  {
	 if ( GetGisType(Para) == GTParaStr )
		KeyboardIn(h->Box, ((GisParaStr*)Para)->s);
  }
  if ( !strcmp(ParaName, "box") || !strcmp(ParaName, "instrument") )
  {
	 if ( GetGisType(Para) == GTParaInt )
		h->Box = ((GisParaInt*)Para)->i;
  }
}

void far ProceedMut(GisReadArtHead *h, char turn)
{
//  *Echo << "["<< (int)turn <<"]";
//  h->Cursor->Echo();
  int Key;
  CurrentId = h->Id;
  CurrentSep = h->Cursor->Sep;
  switch ( GetGisType(h->Cursor))
  {
	 case GTTag:
		if ( ((GisTag*)(h->Cursor))->Id == TTmutabor )
		  MutaborTag(h, ((GisTag*)(h->Cursor))->Para);
	 case GTTagBegin:
		if ( ((GisTag*)(h->Cursor))->Id == TTalter ) return;
		Write->Gis(h->Cursor, turn);
		break;
	 case GTTagEnd:
		if ( (((GisTagEnd*)(h->Cursor))->Begin)->Id == TTalter ) return;
		Write->Gis(h->Cursor, turn);
		break;
	 case GTNote:
		if ( turn == 1 ) return ;
		Key = ((GisNote*)(h->Cursor))->GetKey();
		if ( Key == -1 ) return ;
		Key += h->GetOctave()*12;
		gis_analyse(h->Box, Key, turn);
		break;
	 default:
		Write->Gis(h->Cursor, turn);
  }
}

GisReadArtHead *RHead;

void init_hauptschleife( void )
{
  int i;
  for (i=0;i<16;i++)
	 OutDevices[i]->Open();
}

void uninit_hauptschleife( void )
{
  int i;
  for (i=0;i<16;i++)
	 OutDevices[i]->Close();
}

// ##################################################################
*/
int main(int argc, char* argv [])
{
  // read parameters
  char *MutFile = 0;
  char *GMNFile = 0;
  char KeyBoard[120] = "";
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
		if ( !MutFile )
		{
		  MutFile = strdup(argv[i]);
		  continue;
		}
		if ( !GMNFile )
		{
		  GMNFile = strdup(argv[i]);
		  continue;
		}
		strcat(KeyBoard, argv[i]);
	 }
  // info text
  *Echo << "GMut - GUIDO Mutabor converter, TU Dresden, R.K. 1998, Version 0.60\n";
  if ( Help )
  {
	 *Echo << "for more information please visit:\n";
	 *Echo << "  http://rcswww.urz.tu-dresden.de/~rkrausse/gmut.htm\n";
	 *Echo << "Usage: gmut mutfile[.mut] gmnfile[.gmn] [InitKeys] [options]\n";
	 *Echo << "  mutfile    Mutabor file as used for Mutabor II, Extension .mut\n";
	 *Echo << "  gmnfile    Music file in GUIDO Music Notation\n";
	 *Echo << "  InitKeys   Sequenz of computer keys as input for instrument 0\n";
	 *Echo << "             (to force tonsystems instead of logics use leading \"&\")\n";
	 *Echo << "  Options:\n";
	 *Echo << "    /silent  Convert with no echo at all\n";
	 *Echo << "    /report  Report into file gmut.rep\n";
	 *Echo << "    /help    Shows this help screen\n";
  }
  if ( !GMNFile ) return 1; // to few parameters
  // read *.mut file
  if ( !GMutCompile(ExtCheck(MutFile, "mut")) ) return 0;
  // read *.gmn file
/*  *Echo << "GSP parsing file: " << ExtCheck(GMNFile, "gmn") << " ...";
  GisToken *GisFile = GisParse(ExtCheck(GMNFile, "gmn"));
  if ( GspError )
  {
	 *Echo << "\n  Parsing interupted !\n";
	 *Echo << "  ErrorNr: " << GspError << " - " << GspErrorText[GspError] << "\n";
	 *Echo << "  Line: " << GspErrorLineNr << ", " << GspErrorPos << "\n";
	 *Echo << "  " << GspErrorLine << "\n  ";
	 for (int i = 0; i < GspErrorPos; i++) *Echo << " ";
	 *Echo << "^";
	 return 2;
  }
  else
	 *Echo << " OK\n";
  // translate via mutabor
  // add comment in outputfile
  if ( GisFile->Type() == GTUnknown )
  {
	 char *s = GisFile->Sep;
	 char *s1 = (char*) malloc(strlen(s)+200);
	 strcpy(s1, s);
	 strcat(s1, "\n(* mutated by GMUT Version 0.5 via ");
	 strcat(s1, MutFile);
	 if ( KeyBoard[0] )
	 {
		strcat(s1, " Keys: \"");
		strcat(s1, KeyBoard);
		strcat(s1, "\"");
	 }
	 strcat(s1, " *)\n");
	 GisFile->Sep = s1;
	 free(s);
  }
  // init mutabor
  *Echo << "Translating ...";
  Write = new OutGis("");
  for (i = 0; i < 16; i++)
	 OutDevices[i] = Write;
  global_reset( );
  init_hauptschleife();
  aktionen_init();
  // keyboard analysis
  KeyboardIn(0, KeyBoard);
  // prepare read head
  RHead = new GisReadArtHead(0, GisFile, "");
  RHead->Box = 0;
  (GisReadHead**)RHead->Prev = (GisReadHead**)&RHead;
  // prepare write head
///  WHead = new GisWriteHead(0, "");
  frac z = frac(0,1);
  // main loop
  while ( z >= frac(0,1) )
  {
	 z = GisReadArtHeadOn(&RHead, z, ProceedMut);
	 if ( z > frac(0,1) )
		Write->AddTime(z);
///    *Echo << " " << z << " ";
  }
  *Echo << " OK\n";
  // close mutabor
  uninit_hauptschleife();
  global_reset( );
  // save file
  *Echo << "Saving " << ExtChange(GMNFile, "gmm") << " ...";
  ofstream os = ofstream(ExtChange(GMNFile, "gmm"));
  Write->Head->Data->Stream(os,1);
  os.flush();
  *Echo << " OK\n";
  Echo->flush(); */
  return 0;
}

