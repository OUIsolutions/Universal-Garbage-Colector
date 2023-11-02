


typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*deallocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;

void privateUniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self);


void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);