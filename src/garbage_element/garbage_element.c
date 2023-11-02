



privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void **pointer){
    privateUniversalGarbageElement * self = UniversalGarbage_create_empty_struct(
            self,
            privateUniversalGarbageElement
   );
   self->pointer = pointer;
   self->pointed_value = *pointer;
    return  self;
}

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self){
    if(self->pointed_value){
        free(self->pointed_value);
        self->pointed_value = NULL;
    }
    free(self);
}
