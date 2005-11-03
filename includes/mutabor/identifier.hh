void * mutabor_cls_identifier_constructor(void * _self);
void * mutabor_cls_identifier_destructor(void * _self);
int mutabor_cls_identifier_compare(void * one, void * two);
char * mutabor_cls_identifier_tostring(void * _self);
void * mutabor_cls_identifier_check_cycle(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list);
void mutabor_cls_identifier_precalculate(void * _self);
const void * mutabor_object_identifier;
static struct mutabor_virttable_identifier _mutabor_virttable_identifier = {
    sizeof(struct mutabor_class_identifier),
    "identifier",
    (void **)&mutabor_object_object,
    mutabor_cls_identifier_constructor,
    mutabor_cls_identifier_destructor,
    mutabor_cls_identifier_compare,
    mutabor_cls_identifier_tostring,
    mutabor_cls_identifier_check_cycle,
    mutabor_cls_identifier_precalculate
};
const void * mutabor_object_identifier=&_mutabor_virttable_identifier;
