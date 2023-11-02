

#ifndef UNIVERSAL_GARBAGE_H


#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



#define UNIVERSAL_GARBAGE_OK 0
#define UNIVERSAL_GARBAGE_CLEAR_CALBACK_NOT_PROVIDED -1


#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};

#define UniversalGarbage_cast(value) ((void**)&value)

#define UniversalGarbage_add(garbage,dealocator_callback,value) \
    UniversalGarbage_add_or_resset_raw_func(garbage,dealocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_reallocate(garbage,value) \
    UniversalGarbage_reallocate_raw_func(garbage,UniversalGarbage_cast(value))


#define UniversalGarbage_resset(garbage,value) \
    UniversalGarbage_resset_raw_func(garbage,UniversalGarbage_cast(value))






typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*deallocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;

void privateUniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self);


void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);



typedef  struct UniversalGarbage{

    privateUniversalGarbageElement *main_return;
    privateUniversalGarbageElement **elements;
    int  elements_size;


}UniversalGarbage;

UniversalGarbage * newUniversalGarbage();

void * UniversalGarbage_set_return_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);


void * UniversalGarbage_resset_raw_func(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_reallocate_raw_func(UniversalGarbage *self, void **pointer);

void * UniversalGarbage_add_or_resset_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);







privateUniversalGarbageElement * new_privateUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer){

    privateUniversalGarbageElement * self = UniversalGarbage_create_empty_struct(
        self,
        privateUniversalGarbageElement
    );
    self->pointer = pointer;
    self->deallocator_callback = dealocator_callback;
    self->pointed_value = *pointer;
    return  self;
}
void privateUniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self){
    if(self->pointed_value){
        self->deallocator_callback(self->pointed_value);
        self->pointed_value = NULL;
    }
}

void privateUniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self){
    privateUniversalGarbageSimpleElement_free_pointed_value(self);
    free(self);
}




UniversalGarbage * newUniversalGarbage(){
    UniversalGarbage *self = UniversalGarbage_create_empty_struct(self,UniversalGarbage)
    self->elements = (privateUniversalGarbageElement**)malloc(0);
    return self;
}



void * UniversalGarbage_set_return_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer){

    if(self->main_return){
        privateUniversalGarbageSimpleElement_free_pointed_value(self->main_return);
        self->main_return->pointed_value = *pointer;
    }

    if(!self->main_return){
        self->main_return = new_privateUniversalGarbageSimpleElement(deallocator_callback,pointer);
    }
}

void * UniversalGarbage_reallocate_raw_func(UniversalGarbage *self, void **pointer){

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
void * UniversalGarbage_resset_raw_func(UniversalGarbage *self, void **pointer){

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        bool resset = current->pointer == pointer;
        if(resset){
            privateUniversalGarbageSimpleElement_free_pointed_value(current);
            current->pointed_value = *pointer;
            return  *pointer;
        }
    }
    return  NULL;
}


void * UniversalGarbage_add_or_resset_raw_func(UniversalGarbage *self, void (*deallocator_callback)(void *element), void **pointer){

    if(!pointer){
        return NULL;
    }


    self->elements = (privateUniversalGarbageElement**)realloc(
            self->elements,
            (self->elements_size + 1) * sizeof(privateUniversalGarbageElement*)
    );

    self->elements[self->elements_size] = new_privateUniversalGarbageSimpleElement(deallocator_callback,pointer);
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

    if(self->main_return){
        privateUniversalGarbageSimpleElement_free(self->main_return);
    }

    free(self);
}

void UniversalGarbage_free(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);
    free(self);
}




#define UNIVERSAL_GARBAGE_H
#endif