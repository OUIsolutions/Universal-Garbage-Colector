

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
