

typedef  struct UniversalGarbage{

    privateUniversalGarbageElement *main_return;
    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage();

void * UniversalGarbage_set_simple_type_return(UniversalGarbage *self, void *value);

void * UniversalGarbage_set_complex_type_return(UniversalGarbage *self, short type, void *value);


void * private_UniversalGarbage_resset(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_add_or_resset(UniversalGarbage *self, void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);
