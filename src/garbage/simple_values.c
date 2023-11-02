

void * UniversalGarbage_reallocate_simple_value(UniversalGarbage *self, void **pointer){
    for(int i = 0; i < self->simple_values_size; i++){
        privateUniversalGarbageSimpleElement *current = self->simple_values[i];
        bool reallocate = current->pointer == pointer;
        if(reallocate){
          current->pointed_value = *pointer;
          return *pointer;
        }
    }
    return NULL;
}
void * private_UniversalGarbage_resset_simple_value(UniversalGarbage *self, void **pointer){

    for(int i = 0; i < self->simple_values_size; i++){
        privateUniversalGarbageSimpleElement *current = self->simple_values[i];
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


void* UniversalGarbage_add_or_resset_simple_value(UniversalGarbage *self, void **pointer){

    if(!pointer){
        return NULL;
    }

    void *possible_resset = private_UniversalGarbage_resset_simple_value(self,pointer);
    if(possible_resset){
        return possible_resset;
    }

    self->simple_values = (privateUniversalGarbageSimpleElement**)realloc(
            self->simple_values,
            (self->simple_values_size + 1) * sizeof(privateUniversalGarbageSimpleElement*)
    );

    self->simple_values[self->simple_values_size] = new_privateUniversalGarbageSimpleElement(pointer);
    self->simple_values_size+=1;
    return  *pointer;
}
