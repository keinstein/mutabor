void * mutabor_cls_mutfile_constructor(void * _self);
void * mutabor_cls_mutfile_destructor(void * _self);
int mutabor_cls_object_compare(void * one, void * two);
char * mutabor_cls_mutfile_tostring(void * _self);
const void * mutabor_object_mutfile;
static struct mutabor_virttable_mutfile _mutabor_virttable_mutfile = {
    sizeof(struct mutabor_class_mutfile),
    "mutfile",
    (void **)&mutabor_object_object,
    mutabor_cls_mutfile_constructor,
    mutabor_cls_mutfile_destructor,
    mutabor_cls_object_compare,
    mutabor_cls_mutfile_tostring
};
const void * mutabor_object_mutfile=&_mutabor_virttable_mutfile;
