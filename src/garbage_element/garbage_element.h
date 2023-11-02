


typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*dealocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);