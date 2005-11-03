void * mutabor_cls_intervalSum_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_intervalSum_tostring(void * _self);
void mutabor_cls_intervalDiff_precalculate(void * _self);
void mutabor_cls_identifier_link_childs(void * _self);
const void * mutabor_object_intervalDiff;
static struct mutabor_virttable_intervalDiff _mutabor_virttable_intervalDiff = {
    sizeof(struct mutabor_class_intervalDiff),
    "intervalDiff",
    (void **)&mutabor_object_intervalSum,
    mutabor_cls_intervalSum_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_intervalSum_tostring,
    mutabor_cls_intervalDiff_precalculate,
    mutabor_cls_identifier_link_childs
};
const void * mutabor_object_intervalDiff=&_mutabor_virttable_intervalDiff;
