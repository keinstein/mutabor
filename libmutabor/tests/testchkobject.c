#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <mcheck.h>
#include <stdio.h>
#include <assert.h>
#include "mutabor/intervalDiff.h"

void fatal_error( int nummer, ... ){
}

void show_line_number( int n ){
}

void compiler_warning( int nummer, ... ){
}


void kill_mich(void * s2) {
  fprintf(stderr,"Checking for object ...\n");
  CHK_CLASS(s2,object);
  fprintf(stderr,"Checking for identifier ...\n");
  CHK_CLASS(s2,identifier);
  fprintf(stderr,"Checking for interval ...\n");
  CHK_CLASS(s2,interval);
  fprintf(stderr,"Checking for intervalSum ...\n");
  CHK_CLASS(s2,intervalSum);
  fprintf(stderr,"Checking for intervalDiff ...\n");
  CHK_CLASS(s2,intervalDiff);
}

int main() {
  MUT_CLASS(interval)* o1,*o2;
  MUT_CLASS(intervalSum)* s1,*s2,*s3;

  mtrace();

  fprintf(stderr,"o1\n");
  o1=MUT_NEW(interval);
  assert(o1);
  fprintf(stderr,"o1->copy_name\n");
  MUTABOR_CLASS_FUNCTION(interval,copy_name)(o1,"id1");
  fprintf(stderr,"o1->set_factor\n");
  MUTABOR_CLASS_FUNCTION(interval,set_factor)(o1,3.0);
  fprintf(stderr,"o2\n");
  o2=MUT_NEW(interval);
  assert(o2);
  fprintf(stderr,"o2->copy_name\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(o2,"Id2");
  fprintf(stderr,"o2->set_factor\n");
  MUTABOR_CLASS_FUNCTION(interval,set_factor)(o2,2.9);
  printf("%s\n%s\n",MUT_VIRTCALL(identifier,o1,tostring)(o1),
    MUT_VIRTCALL(object,o2,tostring)(o2));
  fprintf(stderr,"Compare: %d\n",(*(MUT_VIRTTABLE(object)**) o1)->compare(o1,o2));

  s1=MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s1,"Summe 1");
  printf("%s\n",MUT_VIRTCALL(identifier,s1,tostring)(s1));
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s1,o1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s1,o2);
  printf("%s\n",MUT_VIRTCALL(identifier,s1,tostring)(s1));
  
  s2=MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s2,"Summe 2");
  printf("%s\n",MUT_VIRTCALL(identifier,s2,tostring)(s2));
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s2,s1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s2,o2);
  printf("%s\n",MUT_VIRTCALL(identifier,s2,tostring)(s2));
  
  s3=MUT_NEW(intervalDiff);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s2,"Differenz");
  printf("%s\n",MUT_VIRTCALL(identifier,s3,tostring)(s3));
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s3,s1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s3,s2);
  printf("%s\n",MUT_VIRTCALL(identifier,s3,tostring)(s3));

  kill_mich(s2);

  fprintf(stderr,"Deleting s1...\n");
  mutabor_delete(s1);
  fprintf(stderr,"Deleting s2...\n");
  mutabor_delete(s2);
  fprintf(stderr,"Deleting s3...\n");
  mutabor_delete(s3);
  fprintf(stderr,"Deleting o1...\n");
  mutabor_delete(o1);
  fprintf(stderr,"Deleting o2...\n");
  mutabor_delete(o2);
  muntrace();
  return 0;
}
