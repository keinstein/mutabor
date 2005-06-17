/*****  TREIBER GIS Write ************************************/
#include "mutgis.h"
#include "midikern.h"

GisReadArtHead *h;

class GTAK
{
  public:
	 GTAK *Next;
	 GisNote *Note;
	 int Id; // (outinstument << 8) + taste zum identifizieren
	 GTAK(int instr, int taste, GisNote *note, GTAK *next = 0)
	 {
		Next = next;
		Note = note;
		Id = (instr << 8) + taste;
	 }
	 ~GTAK()
	 {
		delete Note;
	 }
};

GTAK *GetGTAK(GTAK *root, int instr, int taste)
{
  int id = (instr << 8) + taste;
  while ( root )
  {
	 if ( root->Id == id ) break;
	 root = root->Next;
  }
  return root;
}

void KillGTAK(GTAK **root, GTAK *gtag)
{
  while ( *root )
  {
	 if ( *root == gtag )
	 {
		*root = gtag->Next;
		delete gtag;
		return;
	 }
	 root = &(*root)->Next;
  }
}

GTAK *Tone = 0;
/*
void gis_note_on(int instr, TONSYSTEM * tonsys, int taste, int velo) {
// Schaltet die Note taste an
  freq = GET_FREQ (taste, tonsys);
  GisNote *Note = new GisNote(zugriff[3]&0x7f, h->GetOctave(), 0, h->Cursor->Sep);
  GisTag *Alter = 0;
  double pitch = (double)(freq & 0x00FFFFFF) / 0x01000000;
  if ( pitch != 0.0 )
  {
	 Alter = new GisTag(TTalter, 0, new GisParaReal(pitch, "> "), "<");
  }
  if ( Alter )
  {
	 GisWriteHeadGis(&WHead, h->Id, Alter, velo);
	 Alter->Para = 0;
	 delete Alter;
  }
  GisWriteHeadGis(&WHead, h->Id, Note, velo);
  Tone = new GTAK(instr, taste, Note, Tone);
}

void gis_note_off(int instr, int taste, int velo)
{
////  freq = GET_FREQ (taste, tonsys);
  GTAK *gtag = GetGTAK(Tone, instr, taste);
  if ( gtag )
  {
	 GisWriteHeadGis(&WHead, h->Id, gtag->Note, velo);
	 KillGTAK(&Tone, gtag);
  }
}
*/
void gis_notes_correct( int instr, TONSYSTEM * tonsys )
{
/*  register int help;
  register int i;
  static int k_alt, f_alt;
// *
  help =ausgabe_instrument[instr][AI_BIS];
  for (i=ausgabe_instrument[instr][AI_VON]; i<=help ; i++ )
	if (ton_auf_kanal[i].taste &&
		  ton_auf_kanal[i].taste != last_note[instr])
	{
	  k_alt=ton_auf_kanal[i].key;
	  f_alt=ton_auf_kanal[i].fine;
	  freq = GET_FREQ (ton_auf_kanal[i].taste, tonsys);
	  if (k_alt!=(ton_auf_kanal[i].key=zugriff[3]&0x7f))
	  {
		 // aus und wieder an
		 if (k_alt) MIDI_OUT3(143+i, k_alt, 0); // alt aus
		 if (zugriff[3]&0x7f)
		 {
			// pitch neu
			MIDI_OUT3(223+i, 1, 64+(ton_auf_kanal[i].fine=zugriff[2]>>2)/bending_range);
			// neu an
			MIDI_OUT3(143+i, zugriff[3]&0x7f, DEFAULTVELO);
		 }
	  }
	  else
		 if (f_alt!=(ton_auf_kanal[i].fine=zugriff[2]>>2))
			// nur pitch bend verändern !
			MIDI_OUT3(223+i, 1, 64+ton_auf_kanal[i].fine/bending_range);
	} * /
  for (i=1; i<=16 ; i++ )
	 if (ton_auf_kanal[i].taste &&
		  ausgabe_instrument[ton_auf_kanal[i].id >> 8][AI_UMLEIT] == instr &&
		  ton_auf_kanal[i].id != last_note_id[instr])
	{
	  k_alt=ton_auf_kanal[i].key;
	  f_alt=ton_auf_kanal[i].fine;
	  freq = GET_FREQ (ton_auf_kanal[i].taste, tonsys);
     if (k_alt!=(ton_auf_kanal[i].key=zugriff[3]&0x7f))
     {
		 // aus und wieder an
		 if (k_alt) MIDI_OUT3(143+i, k_alt, 0); // alt aus
       if (zugriff[3]&0x7f)
       {
			// pitch neu
	      MIDI_PITCH(i);
			// neu an
			MIDI_OUT3(143+i, zugriff[3]&0x7f, DEFAULTVELO);
       }
	  }
	  else
       if (f_alt!=(ton_auf_kanal[i].fine=zugriff[2]>>2))
			// nur pitch bend verändern !
		 {
			MIDI_PITCH(i);
		 }
	}  */
}


void gis_note_on(int instr, TONSYSTEM * tonsys, int taste, int velo) {
// Schaltet die Note taste an
  freq = GET_FREQ (taste, tonsys);
/*  GisWriteAlteredNoteOn(&WHead, h->Id, freq,
	 (instr << 8) + taste, h->GetOctave(), 0, h->Cursor->Sep);  NG*/
}

void gis_note_off(int instr, int taste, int velo)
{
////  freq = GET_FREQ (taste, tonsys);
//NG  GisWriteAlteredNoteOff(&WHead, h->Id, (instr << 8) + taste);
/*  GTAK *gtag = GetGTAK(Tone, instr, taste);
  if ( gtag )
  {
	 GisWriteHeadGis(&WHead, h->Id, gtag->Note, velo);
	 KillGTAK(&Tone, gtag);
  } */
}

void gis_open_synthesizer( void ) {
/* Initialisiert den Synthesizer; Vorbereitung auf Mikrotöne */
}

void gis_close_synthesizer( void ) {
/* Setzt den Synthesizer auf Normalbetrieb zurück */
}


void set_synthesizer_typ_pointers_gis( void )
{ int i;
  for (i=0;i<16;i++) {
		open_synthesizer[i]=gis_open_synthesizer;
		close_synthesizer[i]=gis_close_synthesizer;
		note_on[i]=gis_note_on;
		note_off[i]=gis_note_off;
		notes_correct[i]=gis_notes_correct;
  }
}
