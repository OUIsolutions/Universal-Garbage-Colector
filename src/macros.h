
#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};

#define UniversalGarbage_cast(value) ((void**)&value)

#define UniversalGarbage_add(garbage,dealocator_callback,value) \
    UniversalGarbage_add_or_resset_raw_func(garbage,dealocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_reallocate(garbage,value) \
    UniversalGarbage_reallocate_raw_func(garbage,UniversalGarbage_cast(value))


#define UniversalGarbage_resset(garbage,value) \
    UniversalGarbage_resset_raw_func(garbage,UniversalGarbage_cast(value))

