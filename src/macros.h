
#define UniversalGarbage_empty_null_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};
