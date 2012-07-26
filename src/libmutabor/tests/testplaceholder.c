#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_MCHECK_H
#  include <mcheck.h>
#endif
#include <stdio.h>
#include <assert.h>
#include "mutabor/intervalPlaceholder.h"

void fatal_error( int nummer, ... ){
}

void show_line_number( int n ){
}

void compiler_warning( int nummer, ... ){
}



int main() {
  char * s1,*s2;
  MUT_CLASS(identifier)* o1,*o2;
#ifdef HAVE_MCHECK_H
  mtrace();
#endif
  fprintf(stderr,"Beginn...\n");
  fprintf(stderr,"o1\n");
  o1=MUT_NEW(interval);
  assert(o1);
  fprintf(stderr,"o1->copyname\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(o1,"id1");
  fprintf(stderr,"o2\n");
  o2=MUT_NEW(intervalPlaceholder);
  assert(o2);
  MUTABOR_CLASS_FUNCTION(intervalPlaceholder,copy_name)(o2,"Id2");
  MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement)(o2,o1);
  printf("%s\n%s\n",s1=(*(MUT_VIRTTABLE(identifier)**) o1)->tostring(o1),
    s2=(*(MUT_VIRTTABLE(object)**) o2)->tostring(o2));
  free(s1);free(s2);
  printf("Compare: %d\n",(*(MUT_VIRTTABLE(object)**) o1)->compare(o1,o2));
  printf("Deleting o1...\n");
  mutabor_delete(o1);
  printf("Deleting o2...\n");
  mutabor_delete(o2);
#ifdef HAVE_MCHECK_H
  muntrace();
#endif
  return 0;
}
