

# Universal-Garbage-Colector
Universal-Garbage is an tiny C lib for reducing memory leak problems in C
its designed with the idea of releasing all the memory of each scopes once

# Single File installation
Like any other OUI lib, its designed to be as much easy and as much portable as possible,
so you just need to download the [Single File Version](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/v2.002/UniversalGarbage.h ) and include into your code

## Full Folder
If you want to use with full folder, to make modifications into the source code, you can donwload
the entire **src** project, and include with **src/one.c**

# Understanding Functions and Macros


## UniversalGarbage_add
User the **UniversalGarbage_add** to add a new value to the garbage (it can be NULL)


~~~c

#include "UniversalGarbage.h"

typedef struct Car{
   char *name;
   char *model;
}Car;

Car *newCar(char *name, char *model){
    Car *self  = (Car*)malloc(sizeof(Car));
    self->name = strdup(name);
    self->model = strdup(model);
    return self;
}
void Car_free(Car *self){
    free(self->name);
    free(self->model);
    free(self);
}
int main(){

    UniversalGarbage *garbage = newUniversalGarbage();
    Car *ferrari = newCar("ferrari","red");
    UniversalGarbage_add(garbage, Car_free,ferrari);
    printf("name %s\n",ferrari->name);
    printf("model %s\n",ferrari->model);
    UniversalGarbage_free(garbage);

}


~~~

## UniversalGarbage_add_simple

The **UniversalGarbage_add_simple** works excataly like **UniversalGarbage_add**, but its only works
with values released by **free**


~~~c

#include "UniversalGarbage.h"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add_simple(garbage,test);
    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}

~~~

## UniversalGarbage_resset
Use **UniversalGarbage_resset** to resset an value that already added into the garbage

~~~c

#include "UniversalGarbage.h"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add_simple(garbage,test);

    test = strdup("new test content");
    UniversalGarbage_resset(garbage,test);

    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}


~~~

## UniversalGarbage_add_return
Use **UniversalGarbage_add_return** to define the return of the functions
Its used when an function can return NULL when happend an error


~~~c

#include "UniversalGarbage.h"

typedef struct Car{
   char *name;
   char *model;
}Car;

Car *newCar(char *name, char *model){
    Car *self  = (Car*)malloc(sizeof(Car));
    self->name = strdup(name);
    self->model = strdup(model);
    return self;
}
void Car_free(Car *self){
    free(self->name);
    free(self->model);
    free(self);
}

Car * create_car_or_error(bool generate_error){

    UniversalGarbage *garbage = newUniversalGarbage();
    char *internal_string = strdup("internal string");
    UniversalGarbage_add(garbage, free,internal_string);

    Car *ferrari = newCar("ferrari","red");
    UniversalGarbage_add_return(garbage, Car_free,ferrari);

    if(!generate_error){
        UniversalGarbage_free(garbage);
        return ferrari;
    }

    UniversalGarbage_free_including_return(garbage);
    return  NULL;

}
int main(){
    Car *car_correct = create_car_or_error(false);

    printf("name %s\n",car_correct->name);
    printf("model %s\n",car_correct->model);
    Car_free(car_correct);

    Car *carr_incorrect = create_car_or_error(true);
    if(!carr_incorrect){
        printf("carr incorrect its NULL\n");
    }
    return 0;
}


~~~

# Exemples

In these example we are creating an function that can return an list of numbers, or NULL
and exemplemplificate the lib usage


~~~c

#include "UniversalGarbage.h"


char * create_list(long size, bool generate_error){
    UniversalGarbage  *garbage = newUniversalGarbage();

    char *final_string = (char*)calloc(1,sizeof(char));
    UniversalGarbage_add_simple_return(garbage, final_string);

    char *new_string = NULL;
    UniversalGarbage_add_simple(garbage, new_string);

    for(int i = 0; i < size; i++){

        new_string  = (char*)calloc(20,sizeof(char));
        UniversalGarbage_resset(garbage, new_string);
        sprintf(new_string,"%d\n",i);

        final_string =(char*)realloc(final_string,
                                     (strlen(final_string)+ strlen(new_string) + 2) *sizeof(char)
        );
        UniversalGarbage_reallocate(garbage,final_string);

        strcat(final_string,new_string);
    }

    if(generate_error){
        UniversalGarbage_free_including_return(garbage);
        return NULL;
    }

    UniversalGarbage_free(garbage);
    return final_string;
}



int main(){

    UniversalGarbage *garbage = newUniversalGarbage();
    char *value_a = create_list(5,false);
    UniversalGarbage_add(garbage,free,value_a);

    char *value_b = create_list(5,true);
    UniversalGarbage_add(garbage,free,value_b);

    printf("value a:\n%s\n",value_a);
    printf("value b:\n%s\n",value_b);

    UniversalGarbage_free(garbage);

    return 0;
}


~~~


## Structs
you also can use the garbage inside structs, adding the **garbage** object inside the struct in these way


~~~c


#include "UniversalGarbage.h"

typedef struct Car{
    char *name;
    char *color;
    UniversalGarbage  *garbage;
}Car;

Car *newCar(){
    Car *self = UniversalGarbage_create_empty_struct(self,Car);
    self->garbage = newUniversalGarbage();
    UniversalGarbage_add(self->garbage,free,self);
    UniversalGarbage_add(self->garbage,free,self->name);
    UniversalGarbage_add(self->garbage,free,self->color);
    return self;

}

void Car_set_name(Car*self,const char *name){
    self->name = strdup(name);
    UniversalGarbage_resset(self->garbage,self->name);
}

void Car_set_color(Car*self,const char *color){
    self->color = strdup(color);
    UniversalGarbage_resset(self->garbage,self->color);
}
void Car_free(Car *self){
    UniversalGarbage_free(self->garbage);
}


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();
    Car  *test = newCar();
    //we set Car_free as the dealocator callback
    UniversalGarbage_add(garbage, Car_free,test);
    Car_set_name(test,"ferrari");
    Car_set_color(test,"red");

    printf("model:%s\n",test->name);
    printf("color:%s\n",test->color);
    UniversalGarbage_free(garbage);
}


~~~


