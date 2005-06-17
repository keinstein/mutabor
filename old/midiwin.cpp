// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Windows-MIDI-Funktionen
// ------------------------------------------------------------------

//#define WINVER 0x030A

#ifndef H_MMSYSTEM
  #include <mmsystem.h>
  #define H_MMSYSTEM
#endif

#include "midiauto.h"
#include "midikern.h"
#include "midiwin.h"
#include "record.h"

HMIDIOUT hMidiOut;
HMIDIIN hMidiIn;

int OutputDevice = 0;
int InputDevice = 0;

void pascal _export MidiOpen()
{
  MIDIOUTCAPS miout;
  WORD wSize = sizeof(MIDIOUTCAPS);
  WORD dev = OutputDevice;
  midiOutGetDevCaps(dev, &miout, wSize);
  midiOutOpen(&hMidiOut, dev, NULL, NULL, NULL);
  MIDIINCAPS miin;
  wSize = sizeof(MIDIINCAPS);
  dev = InputDevice;
  midiInGetDevCaps(dev, &miin, wSize);
  midiInOpen(&hMidiIn, dev, (DWORD) MidiInFunc, NULL, CALLBACK_FUNCTION);
  midiInStart(hMidiIn);
}

void pascal _export MidiClose()
{
  midiOutClose(hMidiOut);
  midiInStop(hMidiIn);
  midiInReset(hMidiIn);
  midiInClose(hMidiIn);
}

void MidiOut1(BYTE code)
{
  if ( RecordMode != REC_TRAN )
    midiOutShortMsg(hMidiOut, (DWORD)code);
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(1, code, 1);
#endif
}

void MidiOut2(BYTE code1, BYTE code2)
{
  DWORD code = ((DWORD) code2 <<8) +
               ((DWORD) code1);
  if ( RecordMode != REC_TRAN )
    midiOutShortMsg(hMidiOut, code);
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(1, code, 2);
#endif
}

void MidiOut3(BYTE code1, BYTE code2, BYTE code3)
{
  DWORD code = ((DWORD) code3 << 16) +
               ((DWORD) code2 << 8) +
               ((DWORD) code1);
  if ( RecordMode != REC_TRAN )
    midiOutShortMsg(hMidiOut, code);
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(1, code, 3);
#endif
}

void MidiOut4(BYTE code1, BYTE code2, BYTE code3, BYTE code4)
{
  DWORD code = ((DWORD)code4 << 24) +
               ((DWORD)code3 << 16) +
               ((DWORD)code2 << 8) +
               ((DWORD)code1);
  if ( RecordMode != REC_TRAN )
    midiOutShortMsg(hMidiOut, code);
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(1, code, 4);
#endif
}

void MidiOut(DWORD code)
{
  if ( RecordMode != REC_TRAN )
    midiOutShortMsg(hMidiOut, code);
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(1, code);
#endif
}

