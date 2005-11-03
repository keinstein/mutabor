#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mcheck.h>
#include "mutabor/errors.h"
#include "mutabor/parser.h"

int mutabor_parser_tables_fload (FILE* FP);
#define yydebug mutabor_parser_debug
extern int yydebug;

FILE * mutabor_parser_out;

FILE * tabelle;

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
  exit(300+nr);
}

int main(int argc, char** argv) {
  mtrace();
  if (argc==3) {
    printf("Öffne Tabelle");
    printf("%s\n%s\n",getcwd(NULL,0),argv[1]);
    if ((tabelle=fopen(argv[1],"r"))) {
      printf("Lade Tabelle");
      mutabor_parser_tables_fload(tabelle);
      printf("Schließe Tabelle");
      fclose(tabelle);
    }
    mutabor_parser_out=stderr;
#ifdef DEBUG
    mutabor_debug_level = 0xffff;
    yydebug = 1;
#endif
    printf("%s\n%s\n",get_current_dir_name(),argv[2]);
    mutabor_programm_einlesen(argv[2]);
  }
  muntrace();
  return 0;
}
