



privateUniversalGarbageSimpleElement * new_privateUniversalGarbageSimpleElement(void **pointer){
    privateUniversalGarbageSimpleElement * self = UniversalGarbage_create_empty_struct(
            self,
            privateUniversalGarbageSimpleElement
   );
   self->pointer = pointer;
   self->pointed_value = *pointer;
    return  self;
}

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageSimpleElement *self){
    if(self->pointed_value){
        free(self->pointed_value);
    }
    free(self);
}
