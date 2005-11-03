void * mutabor_cls_intervalPlaceholder_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_intervalPlaceholder_tostring(void * _self);
void * mutabor_cls_intervalPlaceholder_check_cycle(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list);
void mutabor_cls_intervalPlaceholder_precalculate(void * _self);
const void * mutabor_object_intervalPlaceholder;
static struct mutabor_virttable_intervalPlaceholder _mutabor_virttable_intervalPlaceholder = {
    sizeof(struct mutabor_class_intervalPlaceholder),
    "intervalPlaceholder",
    (void **)&mutabor_object_interval,
    mutabor_cls_intervalPlaceholder_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_intervalPlaceholder_tostring,
    mutabor_cls_intervalPlaceholder_check_cycle,
    mutabor_cls_intervalPlaceholder_precalculate
};
const void * mutabor_object_intervalPlaceholder=&_mutabor_virttable_intervalPlaceholder;
