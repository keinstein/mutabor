void * mutabor_cls_interval_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_interval_tostring(void * _self);
void * mutabor_cls_identifier_check_cycle(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list);
void mutabor_cls_identifier_precalculate(void * _self);
const void * mutabor_object_interval;
static struct mutabor_virttable_interval _mutabor_virttable_interval = {
    sizeof(struct mutabor_class_interval),
    "interval",
    (void **)&mutabor_object_identifier,
    mutabor_cls_interval_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_interval_tostring,
    mutabor_cls_identifier_check_cycle,
    mutabor_cls_identifier_precalculate
};
const void * mutabor_object_interval=&_mutabor_virttable_interval;
