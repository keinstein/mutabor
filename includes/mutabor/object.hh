void * mutabor_cls_object_constructor(void * _self);
void * mutabor_cls_object_destructor(void * _self);
int mutabor_cls_object_compare(void * one, void * two);
char * mutabor_cls_object_tostring(void * _self);
const void * mutabor_object_object;
static struct mutabor_virttable_object _mutabor_virttable_object = {
    sizeof(struct mutabor_class_object),
    "object",
    (void **)&mutabor_object_object,
    mutabor_cls_object_constructor,
    mutabor_cls_object_destructor,
    mutabor_cls_object_compare,
    mutabor_cls_object_tostring
};
const void * mutabor_object_object=&_mutabor_virttable_object;
