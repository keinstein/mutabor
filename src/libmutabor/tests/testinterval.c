#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_MCHECK_H
#  include <mcheck.h>
#endif
#include <stdio.h>
#include <assert.h>
#include "mutabor/intervalDiff.h"
#include "mutabor/intervalStretch.h"


void fatal_error( int nummer, ... ){
}

void show_line_number( int n ){
}

void compiler_warning( int nummer, ... ){
}

int main() {
  MUT_CLASS(interval)* o1,*o2, *o3;
  MUT_CLASS(intervalSum)* s1,*s2,*s3;
  char * c1,*c2,*c3;

#ifdef HAVE_MCHECK_H
  mtrace();
#endif
  fprintf(stderr,"o1\n");
  o1=MUT_NEW(interval);
  assert(o1);
  fprintf(stderr,"o1->copy_name\n");
  MUTABOR_CLASS_FUNCTION(interval,copy_name) (o1, "id1");
  fprintf(stderr,"o1->set_factor\n");
  MUTABOR_CLASS_FUNCTION(interval,set_factor) (o1, 3.0);
  fprintf(stderr,"o2\n");
  o2 = MUT_NEW(intervalStretch);
  assert(o2);
  fprintf(stderr,"o2->copy_name\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(o2,"Id2");
  fprintf(stderr,"o2->setstretch\n");
  MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)(o2,2.9);
  MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(o2,o1);
  fprintf(stderr,"o3\n");
  o3 = MUT_NEW(intervalStretch);
  assert(o3);
  fprintf(stderr,"o3->copy_name\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(o3,"Id2");
  fprintf(stderr,"o3->setright\n");
  MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(o3,o2);
  printf("%s\n%s\n%s\n",c1=MUT_VIRTCALL(identifier,o1,tostring)(o1),
	 c2=MUT_VIRTCALL(object,o2,tostring)(o2),
	 c3=MUT_VIRTCALL(object,o3,tostring)(o3));
  free(c1);free(c2);free(c3);
  fprintf(stderr,"Compare: %d\n",(*(MUT_VIRTTABLE(object)**) o1)->compare(o1,o2));

  s1 = MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s1,"Summe 1");
  printf("%s\n",c1=MUT_VIRTCALL(identifier,s1,tostring)(s1));
  free(c1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s1,o1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s1,o2);
  printf("%s\n",c1=MUT_VIRTCALL(identifier,s1,tostring)(s1));
  free(c1);
  
  s2 = MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION (identifier, copy_name) (s2, "Summe 2");
  printf ("%s\n",c1=MUT_VIRTCALL(identifier, s2, tostring) (s2));
  free(c1);
  MUTABOR_CLASS_FUNCTION (intervalSum, setleft) (s2, s1);
  MUTABOR_CLASS_FUNCTION (intervalSum, setright) (s2, o2);
  printf ("%s\n",c1= MUT_VIRTCALL (identifier, s2, tostring) (s2));
  free(c1);
  
  s3=MUT_NEW(intervalDiff);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s3,"Differenz");
  printf("%s\n",c1=MUT_VIRTCALL(identifier,s3,tostring)(s3));
  free(c1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s3,s1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s3,s2);
  printf("%s\n",c1=MUT_VIRTCALL(identifier,s3,tostring)(s3));
  free(c1);
  


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
#ifdef HAVE_MCHECK_H
  muntrace();
#endif
  return 0;
}
