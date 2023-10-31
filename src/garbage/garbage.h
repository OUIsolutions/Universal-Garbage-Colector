

typedef  struct UniversalGarbage{

    void (*clear_callback)(short type, void*value);
    void *main_return;
    void **normal_values;
    int  normal_values_size;
    privateUniversalGarbageElement *especial_values;
    int especial_values_size;

}UniversalGarbage;

UniversalGarbage newUniversalGarbage(UniversalGarbage *self,void (*clear_callback)(short type, void*value));

void UniversalGarbage_add_normal_return(UniversalGarbage *self,void *value);

void UniversalGarbage_add_especial_return(UniversalGarbage *self,short type,void *value);

void UniversalGarbage_add_normal_value(UniversalGarbage *self,void *value);

void UniversalGarbage_add_especial_value(UniversalGarbage *self,short type,void *value);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);
