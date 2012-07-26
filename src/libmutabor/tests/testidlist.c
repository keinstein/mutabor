#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <assert.h>
#ifdef HAVE_MCHECK_H
#  include <mcheck.h>
#endif
#include "mutabor/idlist.h"
#include "mutabor/intervalDiff.h"

void fatal_error( int nummer, ... ){
}

void show_line_number( int n ){
}

void compiler_warning( int nummer, ... ){
}



int main() {
  MUT_CLASS(idlist) *list;
  MUT_CLASS(interval)* o1,*o2;
  MUT_CLASS(intervalSum)* s1,*s2,*s3;
  char * c1,*c2;

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
  list = MUT_NEW(idlist);
  fprintf(stderr,"insert o1\n");
  if(!MUT_VIRTCALL(idlist,list,insert)(list,o1)) assert(0);
  c1=MUT_VIRTCALL(idlist,list,tostring)(list);
  printf("%s\n",c1);
  free(c1);
      
  fprintf(stderr,"o2\n");
  o2=MUT_NEW(interval);
  assert(o2);
  fprintf(stderr,"o2->copy_name\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(o2,"Id2");
  fprintf(stderr,"o2->set_factor\n");
  MUTABOR_CLASS_FUNCTION(interval,set_factor)(o2,2.9);

  fprintf(stderr,"insert o2\n");
  if(!MUT_VIRTCALL(idlist,list,insert)(list,o2)) assert(0);
  fprintf(stderr,"insert o2\n");
    c1=MUT_VIRTCALL(idlist,list,tostring)(list);
  printf("%s\n",c1);
  free(c1);
  
  c1=MUT_VIRTCALL(identifier,o1,tostring)(o1);
  c2=MUT_VIRTCALL(object,o2,tostring)(o2);
  printf("%s\n%s\n",c1,c2);
  free(c1); 
  free(c2);
  fprintf(stderr,"Compare: %d\n",(*(MUT_VIRTTABLE(object)**) o1)->compare(o1,o2));

  s1 = MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s1,"Summe 1");
  c1=MUT_VIRTCALL(identifier,s1,tostring)(s1);
  printf("%s\n",c1);
  free(c1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s1,o1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s1,o2);
  c1=MUT_VIRTCALL(identifier,s1,tostring)(s1);
  printf("%s\n",c1);
  free(c1);

  fprintf(stderr,"insert s1\n");
  if(!MUT_VIRTCALL(idlist,list,insert)(list,s1)) assert(0);
  c1=MUT_VIRTCALL(idlist,list,tostring)(list);
  printf("%s\n",c1);
  free(c1);
    
  s2 = MUT_NEW(intervalSum);
  MUTABOR_CLASS_FUNCTION (identifier, copy_name) (s2, "Summe 2");
  c1=MUT_VIRTCALL(identifier, s2, tostring) (s2);
  printf ("%s\n",c1);
  free(c1);
  MUTABOR_CLASS_FUNCTION (intervalSum, setleft) (s2, s1);
  MUTABOR_CLASS_FUNCTION (intervalSum, setright) (s2, o2);
  c1=MUT_VIRTCALL (identifier, s2, tostring) (s2);
  printf ("%s\n",c1 );
  free(c1);

  fprintf(stderr,"insert s2\n");
  if(!MUT_VIRTCALL(idlist,list,insert)(list,s2)) assert(0);
  fprintf(stderr,"insert s2\n");
  
  fprintf(stderr,"insert s2\n");
  s3=MUT_NEW(intervalDiff);
  fprintf(stderr,"insert s2\n");
  MUTABOR_CLASS_FUNCTION(identifier,copy_name)(s3,"Differenz");
  fprintf(stderr,"insert s2\n");
  c1=MUT_VIRTCALL(identifier,s3,tostring)(s3);
  printf("%s\n",c1);
  free(c1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setright)(s3,s1);
  MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(s3,s2);
  c1=MUT_VIRTCALL(identifier,s3,tostring)(s3);
  printf("%s\n",c1);
  free(c1);
  
  fprintf(stderr,"insert s3\n");
  if(!MUT_VIRTCALL(idlist,list,insert)(list,s3)) assert(0);

  c1=MUT_VIRTCALL(idlist,list,tostring)(list);
  printf("%s\n",c1);
  free(c1);
  
  fprintf(stderr,"Deleting list...\n");
  mutabor_delete(list);
#ifdef HAVE_MCHECK_H
  muntrace();
#endif
  return 0;
}
