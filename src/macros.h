
#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};

#define UniversalGarbage_add_or_resset(garbage,dealocator_callback,value) \
    UniversalGarbage_add_or_resset_raw_func(garbage,dealocator_callback,(void**)&value)

#define UniversalGarbage_reallocate(garbage,value) \
    UniversalGarbage_reallocate_raw_func(garbage,(void**)&value)