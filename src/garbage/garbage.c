

UniversalGarbage * newUniversalGarbage(void (*clear_callback)(short type, void*value)){
    UniversalGarbage *self = (UniversalGarbage*)malloc(sizeof (UniversalGarbage));
    *self = (UniversalGarbage){0};
    self->clear_callback = clear_callback;
    self->is_main_return_a_simple_type = true;
    self->simple_values = (void**)malloc(0);
    self->complex_values =  (privateUniversalGarbageComplexElement**)malloc(0);
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

void * private_UniversalGarbage_resset_simple_value(UniversalGarbage *self, void *new_value){
    if(!self->old_value){
        return NULL;
    }
    for(int i = 0; i < self->simple_values_size; i++){
        void *current = self->simple_values[i];
        if(current == self->old_value){
            free(current);
            self->simple_values[i] = new_value;
            self->old_value = NULL;
            return new_value;
        }
    }
    return  NULL;
}


void* UniversalGarbage_add_simple_value(UniversalGarbage *self, void *value){

    if(!value){
        return NULL;
    }
    void *possible_resset = private_UniversalGarbage_resset_simple_value(self,value);
    if(possible_resset){
        return possible_resset;
    }


    for(int i = 0; i < self->simple_values_size; i++){
        bool already_addedd  = self->simple_values[i] == value;
        if(already_addedd){
            return value;
        }
    }

    self->simple_values = (void**)realloc(
            self->simple_values,
            (self->simple_values_size + 1) * sizeof(void*)
    );
    self->simple_values[self->simple_values_size] = value;
    self->simple_values_size+=1;
    return  value;

}

void * UniversalGarbage_add_complex_value(UniversalGarbage *self, short type, void *value){
    if(!value){
        return NULL;
    }

    self->complex_values = (privateUniversalGarbageComplexElement**) realloc(
                self->complex_values,
                (self->complex_values_size + 1 ) * (sizeof (privateUniversalGarbageComplexElement**))
    );
    self->complex_values[self->complex_values_size] = newprivateUniversalGarbageElement(type, value);
    self->complex_values_size+=1;
    return value;
}

short private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self){
    for(int i = 0; i < self->simple_values_size; i++){
        void *current = self->simple_values[i];
        if(current){
            free(current);
        }
    }
    free(self->simple_values);

    for(int i = 0; i < self->complex_values_size; i++){
        privateUniversalGarbageComplexElement  *current = self->complex_values[i];

        if(current->value &&self->clear_callback){
            self->clear_callback(current->type,current->value);
        }

        if(current->value && !self->clear_callback){
            //these is a potencial error
            free(current->value);
        }

        free(current);

    }
    free(self->complex_values);

    if(!self->clear_callback && self->complex_values_size){
        return UNIVERSAL_GARBAGE_CLEAR_CALBACK_NOT_PROVIDED;
    }
    return UNIVERSAL_GARBAGE_OK;

}

short UniversalGarbage_free_including_return(UniversalGarbage *self){

    short universal_clear_result = private_UniversalGarbage_free_all_sub_elements(self);
    short main_clear_result = private_UniversalGarbage_clear_main_return(self);

    free(self);

    if(universal_clear_result || main_clear_result){
        return UNIVERSAL_GARBAGE_CLEAR_CALBACK_NOT_PROVIDED;
    }

    return UNIVERSAL_GARBAGE_OK;
}

short UniversalGarbage_free(UniversalGarbage *self){
    short universal_clear_result = private_UniversalGarbage_free_all_sub_elements(self);
    free(self);

    return universal_clear_result;
}
