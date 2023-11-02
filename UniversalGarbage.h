

#ifndef UNIVERSAL_GARBAGE_H


#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>





#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};


#define UniversalGarbage_cast(value) ((void**)&value)

#define UniversalGarbage_set_return(garbage,deallocator_callback,value) \
        rawUniversalGarbage_set_return(garbage,(void*)deallocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_set_simple_return(garbage,value) \
    UniversalGarbage_set_return(garbage,free,value)


#define UniversalGarbage_add(garbage,deallocator_callback,value) \
    rawUniversalGarbage_add(garbage,(void*)deallocator_callback,UniversalGarbage_cast(value))

#define  UniversalGarbage_remove(garbage,value) \
    rawUniversalGarbage_remove(garbage,UniversalGarbage_cast(value));


#define  UniversalGarbage_disconnect(garbage,value) \
    rawUniversalGarbage_disconnect(garbage,UniversalGarbage_cast(value));

#define UniversalGarbage_add_simple(garbage,value) \
     UniversalGarbage_add(garbage,free,value)


#define UniversalGarbage_reallocate(garbage,value) \
    rawUniversalGarbage_reallocate(garbage,UniversalGarbage_cast(value))


#define UniversalGarbage_resset(garbage,value) \
    rawUniversalGarbage_resset(garbage,UniversalGarbage_cast(value))






typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*deallocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;

void private_UniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self);


void private_UniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * private_newUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);



typedef  struct UniversalGarbage{

    privateUniversalGarbageElement *main_return;
    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage();


bool private_UniversalGarbage_is_the_main_return(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_set_return(UniversalGarbage *self, void *release_callback, void **pointer);

void  rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_remove(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_disconnect(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

void  rawUniversalGarbage_add(UniversalGarbage *self,  void *release_callback, void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);







privateUniversalGarbageElement * private_newUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer){

    privateUniversalGarbageElement * self = UniversalGarbage_create_empty_struct(
        self,
        privateUniversalGarbageElement
    );
    self->pointer = pointer;
    self->deallocator_callback = dealocator_callback;
    self->pointed_value = *pointer;
    return  self;
}
void private_UniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self){
    if(self->pointed_value){
        self->deallocator_callback(self->pointed_value);
        self->pointed_value = NULL;
    }
}

void private_UniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self){
    private_UniversalGarbageSimpleElement_free_pointed_value(self);
    free(self);
}




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




#define UNIVERSAL_GARBAGE_H
#endif