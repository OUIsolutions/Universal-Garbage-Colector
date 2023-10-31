#include <string.h>
#include <stdio.h>
#include "src/one.h"


typedef struct Car{
    char *name;
    char *color;
    UniversalGarbage  *garbage;
}Car;

Car *newCar(){
    Car *self = (Car*)malloc(sizeof(Car));
    self->garbage = newUniversalGarbage(NULL);
    UniversalGarbage_add_simple_value(self->garbage,self);
    return  self;
}

void Car_set_name(Car*self,const char *name){
    self->name = strdup(name);
    UniversalGarbage_add_simple_value(self->garbage,self->name);
}

void Car_set_color(Car*self,const char *color){
    self->color = strdup(color);
    UniversalGarbage_add_simple_value(self->garbage,self->color);
}

void Car_free(Car *self){
    UniversalGarbage_free(self->garbage);
}
#define CAR 1

void clear_all(short type, void *value){
    if(type == CAR){
        Car_free((Car*)value);
    }
}

int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(clear_all);
    char *test = strdup("aaaaaaaaaaaaaaaaaaa");
    UniversalGarbage_add_simple_value(garbage, test);


    char * test2 = strdup("aaaaaaaaaaa");
    UniversalGarbage_add_simple_value(garbage, test2);

    Car *celta = newCar();
    UniversalGarbage_add_complex_value(garbage,CAR,celta);

    Car_set_color(celta,"vermelho");
    Car_set_name(celta,"aaaaaa");

    printf("nome: %s\n",celta->name);
    printf("cor: %s\n",celta->color);


    UniversalGarbage_free(garbage);
    return 0;
}