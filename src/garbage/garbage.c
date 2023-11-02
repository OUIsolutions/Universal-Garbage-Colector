

UniversalGarbage * newUniversalGarbage(){
    UniversalGarbage *self = UniversalGarbage_create_empty_struct(self,UniversalGarbage)
    self->elements = (privateUniversalGarbageElement**)malloc(0);
    return self;
}


bool private_UniversalGarbage_is_the_main_return(UniversalGarbage *self, void **pointer){
    if(self->main_return){
        return  self->main_return->pointer == pointer;
    }
    return false;
}
void  rawUniversalGarbage_set_return(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer){

    if(self->main_return){
        private_UniversalGarbageSimpleElement_free_pointed_value(self->main_return);
        self->main_return->pointed_value = *pointer;
    }

    if(!self->main_return){
        self->main_return = private_newUniversalGarbageSimpleElement(deallocator_callback, pointer);
    }
}

void  UniversalGarbage_reallocate_raw_func(UniversalGarbage *self, void **pointer){
    bool is_the_main_return = private_UniversalGarbage_is_the_main_return(self,pointer);
    if(is_the_main_return){
        self->main_return->pointed_value = *pointer;
    }

    for(int i = 0; i < self->elements_size; i++){

        privateUniversalGarbageElement *current = self->elements[i];
        bool reallocate = current->pointer == pointer;

        if(reallocate){
            current->pointed_value = *pointer;

        }

    }
}
void  rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer){

    bool is_the_main_return = private_UniversalGarbage_is_the_main_return(self,pointer);
    if(is_the_main_return){
        private_UniversalGarbageSimpleElement_free_pointed_value(self->main_return);
        self->main_return->pointed_value = *pointer;
        return;
    }


    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        bool resset = current->pointer == pointer;
        if(resset){
            private_UniversalGarbageSimpleElement_free_pointed_value(current);
            current->pointed_value = *pointer;
            return;
        }
    }

}


void  rawUniversalGarbage_add_or_resset(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer){

    if(!pointer){
        return;
    }


    self->elements = (privateUniversalGarbageElement**)realloc(
            self->elements,
            (self->elements_size + 1) * sizeof(privateUniversalGarbageElement*)
    );

    self->elements[self->elements_size] = private_newUniversalGarbageSimpleElement(deallocator_callback, pointer);
    self->elements_size+=1;
}



void  private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self){
    for(int i = 0; i < self->elements_size; i++){
        private_UniversalGarbageSimpleElement_free(self->elements[i]);
    }
    free(self->elements);

}

void UniversalGarbage_free_including_return(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);

    if(self->main_return){
        private_UniversalGarbageSimpleElement_free(self->main_return);
    }
    free(self);
}

void UniversalGarbage_free(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);
    free(self->main_return);
    free(self);
}
