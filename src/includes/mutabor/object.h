/** \file
 ***********************************************************************
 * Common definitions for object oriented programming and base class
 * \c #object.
 *
 * $Id: object.h,v 1.5 2008/10/10 08:45:28 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date $Date: 2008/10/10 08:45:28 $
 * \version $Revision: 1.5 $
 *
 * $Log: object.h,v $
 * Revision 1.5  2008/10/10 08:45:28  keinstein
 * myContextHelpButton is still not needed
 *
 * Revision 1.1  2005/11/03 14:02:56  keinstein
 * initial revision
 *
 */

#ifndef __MUTABOR_OBJECT_H__
#define __MUTABOR_OBJECT_H__

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#define CHK_CLASS(object,class) \
  assert(mutabor_check_class((void *)object,(void *)MUT_OBJECT(class)))
#define MUTABOR_EXPAND_MACRO(A) A
#define MUTABOR_CONCAT_NAME_(a,b) a##b
#define MUTABOR_CONCAT_NAME(a,b) MUTABOR_CONCAT_NAME_(a,b)
#define MUT_FUNC(name) MUTABOR_CONCAT_NAME (mutabor_ ,name)
#define MUT_CLASS(name) struct MUTABOR_CONCAT_NAME(mutabor_class_, name)
#define MUT_VALUE(class,object) ((MUT_CLASS(class)*)object)
#define MUT_VIRTTABLE(name) struct MUTABOR_CONCAT_NAME(mutabor_virttable_,name)
#define MUT_OBJECT(name) MUTABOR_CONCAT_NAME(mutabor_object_,name)
#define MUT_VIRTCALL(class,object,name) \
   (*((MUT_VIRTTABLE(class)**) object))->name
#define MUT_NEW(object) mutabor_new((void *)MUT_OBJECT(object))

#define MUTABOR_CLASS_NAME_(deftype,classname) classname
#define MUTABOR_CLASS_NAME(class) MUTABOR_CLASS_NAME_ class


#define MUTABOR_CLASS_FUNCTION(classname,name) \
MUTABOR_CONCAT_NAME(MUTABOR_CONCAT_NAME(MUT_FUNC(cls_),classname), _ ## name)


struct mutabor_class_object {
    MUT_VIRTTABLE(object) * virttable; 
};

struct mutabor_virttable_object {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); /**< Constructor for creating an object. */
    void * (*destructor)(void * _self); /**< Destructor for deleting an object. */
    int (*compare)(void * one, void * two); /**< Simple comparison. */
    char * (*tostring)(void * _self); /**< Stringify for data output. */
};

extern const void * mutabor_object_object;


void * mutabor_new(void * _type);
void mutabor_delete(void * _object);
int mutabor_check_class(void * _self, void * object);







#ifdef OLD_MUTABOR_CLASSES
#define MUTABOR_CLASS_DEFTYPE_(deftype,classname) deftype
#define MUTABOR_CLASS_DEFTYPE(class) MUTABOR_CLASS_DEFTYPE_ class

#define MUTABOR_CLASS_FUNCTION(classname,name) \
MUTABOR_CONCAT_NAME(MUTABOR_CONCAT_NAME(MUT_FUNC(cls_),classname), _ ## name)

#define MUTABOR_VIRTUAL_DATA(class,rettype,name,...)                                          
#define MUTABOR_VIRTUAL_DECLARATION(class,rettype,name,...) \
rettype (*name) (__VA_ARGS__);
#define MUTABOR_VIRTUAL_DEFINITIONS(class,rettype,name,...) \
rettype MUTABOR_CLASS_FUNCTION(MUTABOR_CLASS_NAME(class),name) (__VA_ARGS__);
#define MUTABOR_VIRTUAL_DEFINITION(classname,rettype,name,...) \
rettype MUTABOR_CLASS_FUNCTION(classname,name) (__VA_ARGS__)
#define MUTABOR_VIRTUAL_INITIALIZE(class,rettype,name,...) \
, &MUTABOR_CLASS_FUNCTION(MUTABOR_CLASS_NAME(class),name)
#define MUTABOR_VIRTUAL_PARENT(class,rettype,name,...) 
#define MUTABOR_VIRTUAL_OVERRIDES(...)

#define MUTABOR_FIELD_DATA(class,type,name) \
   type name;
#define MUTABOR_FIELD_DECLARATION(class,type,name)
#define MUTABOR_FIELD_DEFINITIONS(class,type,name)
#define MUTABOR_FIELD_INITIALIZE(class,type,name)
#define MUTABOR_FIELD_PARENT(class,type,name)
#define MUTABOR_FIELD_OVERRIDES(...)

#define MUTABOR_PARENT_DATA(class,name)\
   MUT_CLASS(name) _;
#define MUTABOR_PARENT_DECLARATION(class,name)  \
  MUTABOR_CLASS_DEFINITIONS_ ## name (class)
#define MUTABOR_PARENT_DEFINITIONS(class,name) \
  MUTABOR_CLASS_DEFINITIONS_ ## name ((DEFINITIONS,name)) 
#define  MUTABOR_PARENT_INITIALIZE(class,name) \
  MUTABOR_CLASS_DEFINITIONS_ ## name ((INITIALIZE,name)) 
#define MUTABOR_PARENT_PARENT(class,name)\
  ((MUT_VIRTTABLE(MUTABOR_CLASS_NAME(class))*) MUT_OBJECT(MUTABOR_CLASS_NAME(class)))\
   ->parent=MUT_OBJECT(name);\
  size=sizeof(MUT_VIRTTABLE(name));
#define MUTABOR_PARENT_OVERRIDES(...)

#define MUTABOR_OBJECT_DATA
#define MUTABOR_OBJECT_DECLARATION
#define MUTABOR_OBJECT_DEFINITIONS
#define MUTABOR_OBJECT_INITIALIZE
#define MUTABOR_OBJECT_PARENT _mutabor_virttable_object.parent=&_mutabor_virttable_object;
#define MUTABOR_OBJECT_OVERRIDES

#define MUTABOR_OVERRIDE_DATA(...)
#define MUTABOR_OVERRIDE_DECLARATION(...)
#define MUTABOR_OVERRIDE_DEFINITIONS(class,rettype,name,...) \
rettype MUTABOR_CLASS_FUNCTION(MUTABOR_CLASS_NAME(class),name) (__VA_ARGS__);
#define MUTABOR_OVERRIDE_INITIALIZE(...)
#define MUTABOR_OVERRIDE_PARENT(...)
#define MUTABOR_OVERRIDE_OVERRIDES(class,rettype,name,...) \
  ((MUT_VIRTTABLE(MUTABOR_CLASS_NAME(class))*) MUT_OBJECT(MUTABOR_CLASS_NAME(class)))\
   ->name=&MUTABOR_CLASS_FUNCTION(MUTABOR_CLASS_NAME(class),name);


#define VIRTUAL(class,rettype,name,...)\
  MUTABOR_CONCAT_NAME(MUTABOR_VIRTUAL_,MUTABOR_CLASS_DEFTYPE(class))\
  (class,rettype,name,__VA_ARGS__)
#define OVERRIDE(class,rettype,name,...)\
  MUTABOR_CONCAT_NAME(MUTABOR_OVERRIDE_,MUTABOR_CLASS_DEFTYPE(class))\
  (class,rettype,name,__VA_ARGS__)

#define FIELD(class,type,name)\
  MUTABOR_CONCAT_NAME(MUTABOR_FIELD_,MUTABOR_CLASS_DEFTYPE(class)) \
  (class,type,name)
#define PARENT(class,name) \
  MUTABOR_CONCAT_NAME(MUTABOR_PARENT_,MUTABOR_CLASS_DEFTYPE(class)) \
  (class,name)


#define MUTABOR_DECLARE_CLASS(child) \
MUT_CLASS(child) { \
  MUTABOR_CLASS_DEFINITIONS_ ## child ((DATA,child)) \
    }; \
MUT_VIRTTABLE(child) { \
  size_t size; \
  char * name; \
  void * parent; \
  VIRTUAL((DECLARATION,child),void,init_virttable,void) \
  MUTABOR_CLASS_DEFINITIONS_ ## child ((DECLARATION,child)) \
} ; \
extern void * MUT_OBJECT(child)

#define MUTABOR_INITIALIZE_CLASS(child)\
MUTABOR_CLASS_DEFINITIONS_ ## child ((DEFINITIONS,child))\
MUTABOR_VIRTUAL_DEFINITION(child,void,init_virttable,void); \
static MUT_VIRTTABLE(child) _mutabor_virttable_ ## child = { \
     sizeof(struct mutabor_class_ ## child), \
     #child, \
     NULL\
     VIRTUAL((INITIALIZE,child),void,init_virttable,void) \
     MUTABOR_CLASS_DEFINITIONS_ ## child ((INITIALIZE,child)) \
}; \
void * MUT_OBJECT(child) = &_mutabor_virttable_##child;\
MUTABOR_VIRTUAL_DEFINITION(child,void,init_virttable,void) {\
  void * p1,*p2; \
  size_t size; \
  MUTABOR_CLASS_DEFINITIONS_ ## child ((PARENT,child)) \
  assert(_mutabor_virttable_##child.parent); \
  if (!((MUT_VIRTTABLE(object)*) _mutabor_virttable_##child.parent)->parent){ \
    ((MUT_VIRTTABLE(object)*) _mutabor_virttable_##child.parent)->init_virttable(); \
  } \
  if (((MUT_VIRTTABLE(object)*) _mutabor_virttable_##child.parent)!=&_mutabor_virttable_##child) { \
    p1=(&_mutabor_virttable_##child.parent)+sizeof(void *); \
    p2=(&(((MUT_VIRTTABLE(object)*) _mutabor_virttable_##child.parent)->parent)) \
	 +sizeof(void *); \
    size=size \
	 - ((size_t)&_mutabor_virttable_##child.parent - (size_t)MUT_OBJECT(child)) \
	 - sizeof(void*);\
    memcpy(p1,p2,size);\
  } \
  MUTABOR_CLASS_DEFINITIONS_ ## child((OVERRIDES,child)) \
}			     



MUT_VIRTTABLE(object);
#define MUTABOR_CLASS_DEFINITIONS_object(class) \
  MUTABOR_CONCAT_NAME(MUTABOR_OBJECT_,MUTABOR_CLASS_DEFTYPE(class)) \
  FIELD(class,MUT_VIRTTABLE(object) *,virttable)\
  VIRTUAL(class, void *, constructor, void * _self) \
  VIRTUAL(class, void *, destructor, void * _self) \
  VIRTUAL(class, int, compare, void * one, void * two) \
  VIRTUAL(class, char *, tostring,void * _self)

MUTABOR_DECLARE_CLASS(object);
#endif

#endif /* __MUTABOR_OBJECT_H__ */
