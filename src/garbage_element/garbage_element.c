


privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer){

    privateUniversalGarbageElement * self = UniversalGarbage_create_empty_struct(
        self,
        privateUniversalGarbageElement
    );
    self->pointer = pointer;
    self->dealocator_callback = dealocator_callback;
    self->pointed_value = *pointer;
    return  self;
}

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self){
    if(self->pointed_value){
        self->dealocator_callback(self->pointed_value);
        self->pointed_value = NULL;
    }
    free(self);
}
