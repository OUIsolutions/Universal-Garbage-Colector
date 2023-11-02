

typedef  struct UniversalGarbage{

    privateUniversalGarbageElement *main_return;
    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage();


bool private_UniversalGarbage_is_the_main_return(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_set_return(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);

void  rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_add(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);
