// ------------------------------------------------------------------
// Mutabor 3, 1999, R.Krauﬂe
// Setup-Datenfeld
// ------------------------------------------------------------------

#ifndef SETUP_H
#define SETUP_H

class TSetupData
{
  public:
    TSetupData::TSetupData(bool toneSystem, bool saveEditorFiles)
    {
      ToneSystem = toneSystem;
      Relation = !toneSystem;
      SaveEditorFiles = saveEditorFiles;
    }
	 uint16 ToneSystem;
	 uint16 Relation;
	 uint16 SaveEditorFiles;
};

#endif
