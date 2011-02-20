/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Action.cpp,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2005,2010 TU Dresden
 * \author  R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: Action.cpp,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup GUI
 * \{
 ********************************************************************/

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "Action.h"
#include "GrafKern.h"

// Aktionen ---------------------------------------------------------

bool AktionChanged[MAX_BOX];

class TAktionTrace
{

public:
	unsigned char Box;
	char *Name;
	TAktionTrace *Next;
	TAktionTrace(unsigned char box, char *name)
	{
		Box = box;
		Name = strdup(name);
		Next = 0;
	}

	~TAktionTrace()
	{
		free(Name);
	}
};

TAktionTrace *AktionTraceBase = 0;
TAktionTrace **AktionTraceTail = &AktionTraceBase;

void AktionTraceReset()
{
	while ( AktionTraceBase ) {
		TAktionTrace *a = AktionTraceBase;
		AktionTraceBase = a->Next;
		delete a;
	}

	AktionTraceTail = &AktionTraceBase;

	for (int i = 0; i < MAX_BOX; i++)
		AktionChanged[i] = false;
}

bool TakeOverAktions()
{
	unsigned char *Boxes;
	int *l, p = 0;
	char *s, sHelp[100];
	int n = GetActString(&Boxes, &l, &s);

	for (int i = 0; i < n; i++) {
		int l1 = l[i]-p;
		strncpy(sHelp,&s[p], l1);
		sHelp[l1] = 0;
		p = l[i];
		*AktionTraceTail = new TAktionTrace(Boxes[i], sHelp);
		AktionTraceTail = &((*AktionTraceTail)->Next);
		AktionChanged[Boxes[i]] = true;
	}

	return n != 0;
}

bool ACTChanged(int box)
{
	bool flag = AktionChanged[box];
	AktionChanged[box] = false;
	return flag;
}


char sAktion[2000];
int ActLineNumbers;

char *GenerateACTString(int box)
{
	strcpy(sAktion, "");
	ActLineNumbers = 0;

	for ( TAktionTrace *a = AktionTraceBase; a; a = a->Next)
		if ( a->Box == box ) {
			while ( strlen(sAktion) > 1900 ) {
				char *s = strchr(sAktion, '\n');
				strcpy(sAktion, &s[1]);
				ActLineNumbers--;
			}

			if ( sAktion[0] )
				strcat(sAktion, "\n");

			strcat(sAktion, a->Name);

			ActLineNumbers++;
		}

	return sAktion;
}

char *GenerateCAWString()
{
	sAktion[0] = 0;
	ActLineNumbers = 0;

	for ( TAktionTrace *a = AktionTraceBase; a; a = a->Next) {
		while ( strlen(sAktion) > 1900 ) {
			char *s = strchr(sAktion, '\n');
			strcpy(sAktion, &s[1]);
			ActLineNumbers--;
		}

		if ( sAktion[0] )
			strcat(sAktion, "\n");

		char sForm[100];

		sprintf(sForm, "Box %3d: %s", a->Box, a->Name);

		strcat(sAktion, sForm);

		ActLineNumbers++;
	}

	return sAktion;
}


///\}
