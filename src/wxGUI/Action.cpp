/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Action.cpp,v 1.8 2012/02/18 18:17:23 keinstein Exp $
 * Copyright:   (c) 2005,2010 TU Dresden
 * \author  R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2012/02/18 18:17:23 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: Action.cpp,v $
 * Revision 1.8  2012/02/18 18:17:23  keinstein
 * reset change flag of boxes after reading it
 *
 * Revision 1.7  2011-11-02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.6  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-08 18:50:41  keinstein
 * Fix some further update bug
 *
 * Revision 1.4  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.3  2011-02-20 22:35:56  keinstein
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

#include "src/kernel/Defs.h"

#include "src/wxGUI/Action.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/box.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// Aktionen ---------------------------------------------------------

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
		mut_box[i].action_changed = false;
}

bool TakeOverActions()
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
		mut_box[i].action_changed = 1;
	}

	return n != 0;
}

bool ACTChanged(int box)
{
	bool flag = mut_box[box].action_changed != 0;
	mut_box[box].action_changed = 0;
	return flag;
}


char sAktion[2000];
int ActLineNumbers;

char *GenerateACTString(int box)
{
	strcpy(sAktion, "");
	ActLineNumbers = 0;

	for ( TAktionTrace *a = AktionTraceBase; a; a = a->Next)
		if ( a->Box == box && a->Name ) {
			int maxsize = 1999-strlen(a->Name)-strlen("\n");
			if (maxsize < 0) maxsize = 0;
			int size = strlen(sAktion);
			if (size>maxsize) {
				char * s = strchr(sAktion+size-maxsize, '\n');
				char * s2 = sAktion;

				while ((s2=strchr(s2+1,'\n')) < s)
					ActLineNumbers--;
				if (s != sAktion)
					ActLineNumbers--;

				if (s) {
					memmove(sAktion,s+1,size-(s-sAktion)-1);
					size -= s-sAktion + 1;
				} else {
					sAktion[0]=0;
					size = 0;
				}
			}

			if ( size ) {
				strcpy(sAktion+size, "\n");
				size += strlen("\n");
			}

			strncat(sAktion+size, a->Name,1999-size);
			sAktion[1999]=0;

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
