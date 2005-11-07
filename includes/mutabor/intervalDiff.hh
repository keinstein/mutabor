void * mutabor_cls_intervalSum_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_intervalSum_tostring(void * _self);
void * mutabor_cls_intervalSum_check_cycle(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list);
void mutabor_cls_intervalDiff_precalculate(void * _self);
const void * mutabor_object_intervalDiff;
static struct mutabor_virttable_intervalDiff _mutabor_virttable_intervalDiff = {
    sizeof(struct mutabor_class_intervalDiff),
    "intervalDiff",
    (void **)&mutabor_object_intervalSum,
    mutabor_cls_intervalSum_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_intervalSum_tostring,
    mutabor_cls_intervalSum_check_cycle,
    mutabor_cls_intervalDiff_precalculate
};
const void * mutabor_object_intervalDiff=&_mutabor_virttable_intervalDiff;
