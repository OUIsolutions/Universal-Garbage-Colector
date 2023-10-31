

UniversalGarbage newUniversalGarbage(void (*clear_callback)(short type, void*value)){
    UniversalGarbage self = {0};
    self.clear_callback = clear_callback;
    self.is_main_a_normal_value = true;
    self.normal_values = (void*)malloc(0);
    self.especial_values =  (privateUniversalGarbageElement*)malloc(0);
    return self;
}
short private_UniversalGarbage_clear_main_return(UniversalGarbage *self){
    if(!self->main_return){
        return UNIVERSAL_GARBAGE_OK;
    }
    if(self->is_main_a_normal_value){
        free(self->main_return);
        return UNIVERSAL_GARBAGE_OK;
    }
    if(!self->clear_callback){
        return UNIVERSAL_GARBAGE_CLEAR_CALBACK_NOT_PROVIDED;
    }

    self->clear_callback(self->main_return_type,self->main_return);
}

void UniversalGarbage_add_normal_return(UniversalGarbage *self,void *value){
    private_UniversalGarbage_clear_main_return(self);
    self->main_return = value;
    self->is_main_a_normal_value = true;
}

void UniversalGarbage_add_especial_return(UniversalGarbage *self,short type,void *value){
    private_UniversalGarbage_clear_main_return(self);
    self->main_return = value;
    self->main_return_type = type;
    self->is_main_a_normal_value = false;
}


void UniversalGarbage_add_normal_value(UniversalGarbage *self,void *value){
    self->normal_values = (void*)realloc(
            self->normal_values,
            (self->normal_values_size +1)* sizeof(void*)
    );
    self->normal_values[self->normal_values_size] = value;
    self->normal_values_size+=1;
}

void UniversalGarbage_add_especial_value(UniversalGarbage *self,short type,void *value){
    self->especial_values = (privateUniversalGarbageElement**) realloc(
                self->especial_values,
               ( self->especial_values_size +1 )* (sizeof (privateUniversalGarbageElement**))
    );
    self->especial_values[self->especial_values_size] = newprivateUniversalGarbageElement(type,value);
}


