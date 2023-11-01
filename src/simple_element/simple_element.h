


typedef struct privateUniversalGarbageSimpleElement{
    void **pointer;
    void *pointed_value;
}privateUniversalGarbageSimpleElement;

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageSimpleElement *self);

privateUniversalGarbageSimpleElement * new_privateUniversalGarbageSimpleElement(void **pointer);