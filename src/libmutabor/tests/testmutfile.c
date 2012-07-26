#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_MCHECK_H
#  include <mcheck.h>
#endif
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "mutabor/errors.h"
#include "mutabor/parser.h"
#include "mutabor/mutfile.h"

extern int mutabor_parser_debug;

void compiler_warning( int nr, ... )
{
  va_list arglist;

  va_start(arglist,nr); 
  fprintf(stderr,"Warnung: ");
  fprintf(stderr,Warning_text[nr], arglist );
}

void fatal_error( int nr, ... ) 
{
  va_list arglist;

  va_start(arglist,nr); 
  fprintf(stderr,"Fehler: ");
  if (mutabor_debug_level)
    fprintf(stderr,"Nr. %d ",nr);
  vfprintf(stderr,Error_text[nr], arglist /* arglist */);
  fprintf(stderr,"\n");
}


int main() {
  MUT_CLASS(mutfile) *file;
  char * c1;

#ifdef HAVE_MCHECK_H
  mtrace();
#endif

  /*  mutabor_parser_debug = 1; */
  file = MUT_NEW(mutfile);
  assert(file);

  MUTABOR_CLASS_FUNCTION(mutfile,setfilename)(file,"Demo.mut");
  MUTABOR_CLASS_FUNCTION(mutfile,parse)(file);

  c1=(*(MUT_VIRTTABLE(mutfile)**) file)->tostring(file);
  printf("%s\n",c1);
  free(c1);

  mutabor_delete(file);

#ifdef HAVE_MCHECK_H
  muntrace();
#endif
  return 0;
}
