void * mutabor_cls_ptrlist_constructor(void * _self);
void * mutabor_cls_ptrlist_destructor(void * _self);
int mutabor_cls_object_compare(void * one, void * two);
char * mutabor_cls_ptrlist_tostring(void * _self);
int mutabor_cls_ptrlist_insert(void * _self,const void * ptr);
void * mutabor_cls_ptrlist_find(void const * _self, void const * ptr);
const void * mutabor_object_ptrlist;
static struct mutabor_virttable_ptrlist _mutabor_virttable_ptrlist = {
    sizeof(struct mutabor_class_ptrlist),
    "ptrlist",
    (void **)&mutabor_object_object,
    mutabor_cls_ptrlist_constructor,
    mutabor_cls_ptrlist_destructor,
    mutabor_cls_object_compare,
    mutabor_cls_ptrlist_tostring,
    mutabor_cls_ptrlist_insert,
    mutabor_cls_ptrlist_find
};
const void * mutabor_object_ptrlist=&_mutabor_virttable_ptrlist;
