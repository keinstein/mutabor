// ##################################################################
// GMN2MIDI (GMN-MIDI-Converter)
// ##################################################################

#include "ext.h"
#include "gsp.h"
#include "gis.h"
#include "gis_head.h"
#include <iostream.h>
#include "mis.h"

MisFile *Midi = new MisFile("");

void far Write(GisReadArtHead *h, char turn)
{
/*  cout << "["<< (int)turn <<"]";
  h->Cursor->Echo(); */
  Midi->WriteGis(h, h->Cursor, turn, 0);
}

// ##################################################################

int main(int argc, char* argv [])
{
  cout << "GMN2MIDI - GUIDO MIDI converter, R.K. 1998, Version 0.5\n";
  if ( argc < 2 )
  {
	 cout << "This is a very rough tool for testing GMut.";
	 cout << "For more information please visit:\n";
	 cout << "  http://rcswww.urz.tu-dresden.de/~rkrausse/gmut.htm\n";
	 cout << "A real good converter by L.Martin will be soon accessible anyhow via:\n";
	 cout << "  http://www.informatik.tu-darmstadt.de/AFS/CM/GUIDO/index.html\n";
	 cout << "Usage:   gmn2midi gmnfile[.gmn] [midfile[.mid]]\n";
	 return 1;
  }
  cout << "Parsing " << ExtCheck(argv[1], "gmn") << " ...";
  GisToken *Gis= GisParse(ExtCheck(argv[1], "gmn"));
  int Result = GspError;
  if ( Result )
  {
	 cout << " Error.\nErrorNr: " << Result << ": " << GspErrorText[Result] << "\n";
	 cout << "Line: " << GspErrorLineNr << ", " << GspErrorPos << "\n";
	 cout << GspErrorLine << "\n";
	 for (int i = 0; i < GspErrorPos; i++) cout << " ";
	 cout << "^";
	 return 2;
  }
  else
	 cout << " OK\n";
  cout << "Translating to MIDI ...";
  GisReadArtHead *RHead = new GisReadArtHead(0, Gis, "");
  (GisReadHead**)RHead->Prev = (GisReadHead**)&RHead;
  frac z = frac(0,1);
  Midi->WriteInit();
  Midi->AddInstrument(0, 0, 15);
  while ( z >= frac(0,1) )
  {
	 z = GisReadArtHeadOn(&RHead, z, Write);
	 if ( z > frac(0,1) )
		Midi->CountOnDeltaTime(z.n*24*16/z.d);
///    cout << " " << z << " ";
  }
  cout << " OK\n";
  char FileName[120];
  if ( argc > 2 )
	 strcpy(FileName, ExtCheck(argv[2], "mid"));
  else
	 strcpy(FileName, ExtChange(argv[1], "mid"));
  cout << "Saving " << FileName << " ...";
  Midi->Save(FileName);
  cout << " OK\n";
  delete Gis;
  return 0;
}

