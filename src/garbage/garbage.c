

UniversalGarbage * newUniversalGarbage(){
    UniversalGarbage *self = UniversalGarbage_create_empty_struct(self,UniversalGarbage)
    self->elements = (privateUniversalGarbageElement**)malloc(0);
    return self;
}


short private_UniversalGarbage_clear_main_return(UniversalGarbage *self){
    if(!self->main_return){
        return UNIVERSAL_GARBAGE_OK;
    }
    if(self->is_main_return_a_simple_type){
        free(self->main_return);
        return UNIVERSAL_GARBAGE_OK;
    }
    if(!self->clear_callback){
        free(self->main_return);
        return UNIVERSAL_GARBAGE_CLEAR_CALBACK_NOT_PROVIDED;
    }

    self->clear_callback(self->main_return_type,self->main_return);
    return  UNIVERSAL_GARBAGE_OK;
}

void *UniversalGarbage_set_simple_type_return(UniversalGarbage *self, void *value){
    private_UniversalGarbage_clear_main_return(self);
    self->main_return = value;
    self->is_main_return_a_simple_type = true;
    return  value;
}

void *UniversalGarbage_set_complex_type_return(UniversalGarbage *self, short type, void *value){
    private_UniversalGarbage_clear_main_return(self);
    self->main_return = value;
    self->main_return_type = type;
    self->is_main_return_a_simple_type = false;
    return  value;
}

void * UniversalGarbage_reallocate(UniversalGarbage *self, void **pointer){

    for(int i = 0; i < self->elements_size; i++){

        privateUniversalGarbageElement *current = self->elements[i];
        bool reallocate = current->pointer == pointer;

        if(reallocate){
            current->pointed_value = *pointer;
            return *pointer;
        }

    }
    return NULL;
}
void * private_UniversalGarbage_resset(UniversalGarbage *self, void **pointer){

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        bool resset = current->pointer == pointer;
        if(resset){
            if(current->pointed_value){
                free(current->pointed_value);
            }
            current->pointed_value = *pointer;
            return  *pointer;
        }
    }
    return  NULL;
}


void* UniversalGarbage_add_or_resset(UniversalGarbage *self, void **pointer){

    if(!pointer){
        return NULL;
    }

    void *possible_resset = private_UniversalGarbage_resset(self, pointer);
    if(possible_resset){
        return possible_resset;
    }

    self->elements = (privateUniversalGarbageElement**)realloc(
            self->elements,
            (self->elements_size + 1) * sizeof(privateUniversalGarbageElement*)
    );

    self->elements[self->elements_size] = new_privateUniversalGarbageSimpleElement(pointer);
    self->elements_size+=1;
    return  *pointer;
}



void  private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self){
    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageSimpleElement_free(self->elements[i]);
    }
    free(self->elements);

}

void UniversalGarbage_free_including_return(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);
    private_UniversalGarbage_clear_main_return(self);
    free(self);
}

void UniversalGarbage_free(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);
    free(self);
}
