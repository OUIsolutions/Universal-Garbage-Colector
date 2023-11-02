
#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};


#define UniversalGarbage_cast(value) ((void**)&value)

#define UniversalGarbage_set_return(garbage,deallocator_callback,value) \
        rawUniversalGarbage_set_return(garbage,(void*)deallocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_set_simple_return(garbage,value) \
    UniversalGarbage_set_return(garbage,free,value)


#define UniversalGarbage_add(garbage,deallocator_callback,value) \
    rawUniversalGarbage_add(garbage,(void*)deallocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_add_simple(garbage,value) \
     UniversalGarbage_add(garbage,free,value)


#define UniversalGarbage_reallocate(garbage,value) \
    rawUniversalGarbage_reallocate(garbage,UniversalGarbage_cast(value))


#define UniversalGarbage_resset(garbage,value) \
    rawUniversalGarbage_resset(garbage,UniversalGarbage_cast(value))

