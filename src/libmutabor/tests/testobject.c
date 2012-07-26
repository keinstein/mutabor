#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_MCHECK_H
#  include <mcheck.h>
#endif
#include <stdio.h>
#include <assert.h>
#include "mutabor/object.h"

int compiler_warning;
int fatal_error;

int main() {
  MUT_CLASS(object) *o1, *o2;
  char *c1,*c2;
#ifdef HAVE_MCHECK_H  
  mtrace();
#endif
  o1 = MUT_NEW(object);
  assert(o1);
  o2 = MUT_NEW(object);
  assert(o2);
  printf("%s\n%s\n",c1=(*(MUT_VIRTTABLE(object)**) o1)->tostring(o1),
    c2=(*(MUT_VIRTTABLE(object)**) o2)->tostring(o2));
  free(c1);
  free(c2);
  printf("Compare: %d\n",(*(MUT_VIRTTABLE(object)**) o1)->compare(o1,o2));
  mutabor_delete(o1);
  mutabor_delete(o2);
#ifdef HAVE_MCHECK_H  
  muntrace();
#endif
  return 0;
}
