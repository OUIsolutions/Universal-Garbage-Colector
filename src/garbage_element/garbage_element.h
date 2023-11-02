


typedef struct privateUniversalGarbageElement{
    void **pointer;
    void *pointed_value;
}privateUniversalGarbageElement;

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void **pointer);