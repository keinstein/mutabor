void * mutabor_cls_intervalStretch_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_intervalStretch_tostring(void * _self);
void * mutabor_cls_intervalStretch_check_cycle(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list);
void mutabor_cls_intervalStretch_precalculate(void * _self);
const void * mutabor_object_intervalStretch;
static struct mutabor_virttable_intervalStretch _mutabor_virttable_intervalStretch = {
    sizeof(struct mutabor_class_intervalStretch),
    "intervalStretch",
    (void **)&mutabor_object_interval,
    mutabor_cls_intervalStretch_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_intervalStretch_tostring,
    mutabor_cls_intervalStretch_check_cycle,
    mutabor_cls_intervalStretch_precalculate
};
const void * mutabor_object_intervalStretch=&_mutabor_virttable_intervalStretch;
