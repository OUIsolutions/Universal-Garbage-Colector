

typedef  struct UniversalGarbage{

    void (*clear_callback)(short type, void*value);
    void *main_return;
    short main_return_type;
    void *old_value;
    bool is_main_return_a_simple_type;

    privateUniversalGarbageSimpleElement **simple_values;
    int  simple_values_size;

    privateUniversalGarbageComplexElement **complex_values;
    int complex_values_size;

}UniversalGarbage;

UniversalGarbage * newUniversalGarbage(void (*clear_callback)(short type, void*value));

void * UniversalGarbage_set_simple_type_return(UniversalGarbage *self, void *value);

void * UniversalGarbage_set_complex_type_return(UniversalGarbage *self, short type, void *value);

void * private_UniversalGarbage_resset_simple_value(UniversalGarbage *self,  void *new_value);

void * UniversalGarbage_add_simple_value(UniversalGarbage *self, void *value);

void * UniversalGarbage_add_complex_value(UniversalGarbage *self, short type, void *value);

short private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

short UniversalGarbage_free_including_return(UniversalGarbage *self);

short UniversalGarbage_free(UniversalGarbage *self);
