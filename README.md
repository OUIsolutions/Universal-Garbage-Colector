

# Universal-Garbage-Colector
Universal-Garbage is an tiny C lib for reducing memory leak problems in C
its designed with the idea of releasing all the memory of each scopes once


# Release
| Item | Description |
| --- | --- |
|[UniversalGarbage.c](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.c)| Definition  | 
|[UniversalGarbage.h](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.h)|Declaration|
|[UniversalGarbageOne.c](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbageOne.c)| One file version|
|[UniversalGarbage.zip](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.zip)| All files|


## UniversalGarbage_add
User the **UniversalGarbage_add** to add a new value to the garbage (it can be NULL)


~~~c

#include "UniversalGarbageOne.c"

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

#include "UniversalGarbageOne.c"


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

#include "UniversalGarbageOne.c"


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

#include "UniversalGarbageOne.c"

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
