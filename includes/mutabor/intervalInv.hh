void * mutabor_cls_intervalPlaceholder_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_interval_compare(void * one, void * two);
char * mutabor_cls_intervalPlaceholder_tostring(void * _self);
void mutabor_cls_intervalInv_precalculate(void * _self);
void mutabor_cls_identifier_link_childs(void * _self);
const void * mutabor_object_intervalInv;
static struct mutabor_virttable_intervalInv _mutabor_virttable_intervalInv = {
    sizeof(struct mutabor_class_intervalInv),
    "intervalInv",
    (void **)&mutabor_object_intervalPlaceholder,
    mutabor_cls_intervalPlaceholder_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_interval_compare,
    mutabor_cls_intervalPlaceholder_tostring,
    mutabor_cls_intervalInv_precalculate,
    mutabor_cls_identifier_link_childs
};
const void * mutabor_object_intervalInv=&_mutabor_virttable_intervalInv;
