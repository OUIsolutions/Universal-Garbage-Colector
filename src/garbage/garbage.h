

typedef  struct UniversalGarbage{

    void (*clear_callback)(short type, void*value);
    void *main_return;
    short main_return_type;
    bool is_main_return_a_simple_type;

    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage(void (*clear_callback)(short type, void*value));

void * UniversalGarbage_set_simple_type_return(UniversalGarbage *self, void *value);

void * UniversalGarbage_set_complex_type_return(UniversalGarbage *self, short type, void *value);


void * private_UniversalGarbage_resset(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_add_or_resset(UniversalGarbage *self, void **pointer);


short private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

short UniversalGarbage_free_including_return(UniversalGarbage *self);

short UniversalGarbage_free(UniversalGarbage *self);
