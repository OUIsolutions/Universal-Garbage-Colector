

typedef  struct UniversalGarbage{

    privateUniversalGarbageElement *main_return;
    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage();

void * UniversalGarbage_set_return_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);

void * UniversalGarbage_resset_raw_func(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_reallocate_raw_func(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_add_or_resset_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);
