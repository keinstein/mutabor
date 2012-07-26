void * mutabor_cls_idlist_constructor(void * _self);
void * mutabor_cls_idlist_destructor(void * _self);
int mutabor_cls_object_compare(void * one, void * two);
char * mutabor_cls_idlist_tostring(void * _self);
int mutabor_cls_idlist_insert(void * _self,const void * identifier);
MUT_CLASS(identifier) * mutabor_cls_idlist_find(void * _self,const char * name);
const void * mutabor_object_idlist;
static struct mutabor_virttable_idlist _mutabor_virttable_idlist = {
    sizeof(struct mutabor_class_idlist),
    "idlist",
    (void **)&mutabor_object_object,
    mutabor_cls_idlist_constructor,
    mutabor_cls_idlist_destructor,
    mutabor_cls_object_compare,
    mutabor_cls_idlist_tostring,
    mutabor_cls_idlist_insert,
    mutabor_cls_idlist_find
};
const void * mutabor_object_idlist=&_mutabor_virttable_idlist;
