

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
void  rawUniversalGarbage_set_return(UniversalGarbage *self, void *release_callback, void **pointer){

    if(self->main_return){
        private_UniversalGarbageSimpleElement_free_pointed_value(self->main_return);
        self->main_return->pointed_value = *pointer;
    }

    if(!self->main_return){
        void (*dealocator_callback)(void *element);
        #ifdef __cplusplus
                dealocator_callback =reinterpret_cast<void(*)(void*)>(release_callback);
        #else
                dealocator_callback = (void*)(void*)release_callback;
        #endif
        self->main_return = private_newUniversalGarbageSimpleElement(dealocator_callback, pointer);
    }
}

void  rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer){
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
void  rawUniversalGarbage_remove(UniversalGarbage *self, void **pointer){
    bool is_the_main_return = private_UniversalGarbage_is_the_main_return(self,pointer);
    if(is_the_main_return){
        private_UniversalGarbageSimpleElement_free(self->main_return);
        *pointer = NULL;
        return;
    }
    const int NOTHING_REMOVED = -1;
    int removed_point = NOTHING_REMOVED;

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        if(current->pointer == pointer){
            private_UniversalGarbageSimpleElement_free(current);
            self->elements_size-=1;
            removed_point = i;
            break;
        }
    }

    if(removed_point == NOTHING_REMOVED){
        return;
    }
    for(int i= removed_point; i< self->elements_size;i++){
        self->elements[i] = self->elements[i+1];
    }

    *pointer = NULL;

}
void  rawUniversalGarbage_disconnect(UniversalGarbage *self, void **pointer){
    bool is_the_main_return = private_UniversalGarbage_is_the_main_return(self,pointer);
    if(is_the_main_return){
        free(self->main_return);
        return;
    }

    const int NOTHING_REMOVED = -1;
    int removed_point = NOTHING_REMOVED;

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        if(current->pointer == pointer){
            free(current);
            self->elements_size-=1;
            removed_point = i;
            break;
        }
    }

    if(removed_point == NOTHING_REMOVED){
        return;
    }
    for(int i= removed_point; i< self->elements_size;i++){
        self->elements[i] = self->elements[i+1];
    }

}
void  rawUniversalGarbage_add(UniversalGarbage *self, void *release_callback, void **pointer){

    if(!pointer){
        return;
    }


    self->elements = (privateUniversalGarbageElement**)realloc(
            self->elements,
            (self->elements_size + 1) * sizeof(privateUniversalGarbageElement*)
    );
    void (*dealocator_callback)(void *element);
#ifdef __cplusplus
    dealocator_callback =reinterpret_cast<void(*)(void*)>(release_callback);
#else
    dealocator_callback = (void*)(void*)release_callback;

#endif
    self->elements[self->elements_size] = private_newUniversalGarbageSimpleElement(dealocator_callback, pointer);
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
