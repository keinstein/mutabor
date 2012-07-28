/** \file ext.cpp
 ******************************************************************
 * Some tine fancy tools for file names
 ******************************************************************/


#include "ext.h"
#include <string.h>

char sHelp[120]; //!< return value for ExtCheck and ExtChange functions

/**
 **************************************************************************
 *  Append a extension to a file name if it does not exist.
 *  \param[in] fileName Filename the extension has to be added to
 *  \param[in] extension Extension which should be added 
 *  \bug possible buffer overflow for sHelp (no length check)
 **************************************************************************/

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

/**
 *************************************************************************
 *  Exchanges the extension of a file name.
 * 
 * \param[in] fileName Filename the extension has to be added to
 * \param[in] extension Extension which should be added 
 * \bug possible buffer overflow for sHelp (no length check)
 * \bug first dot in filename used to detect extension, but not last one.
 *************************************************************************/
  
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

