// ##################################################################
// EXT (some tine fancy tools for file names)
// ##################################################################

#include "ext.h"
#include <string.h>

char sHelp[120];

char *ExtCheck(char *fileName, char *extension)
{
  strcpy(sHelp, fileName);
  if ( !strchr(sHelp, '.') )
  {
	 strcat(sHelp, ".");
	 strcat(sHelp, extension);
  }
  return sHelp;
}

char *ExtChange(char *fileName, char *extension)
{
  strcpy(sHelp, fileName);
  char *s1 = strchr(sHelp, '.');
  if ( s1 )
	 s1[0] = 0;
  strcat(sHelp, ".");
  strcat(sHelp, extension);
  return sHelp;
}

