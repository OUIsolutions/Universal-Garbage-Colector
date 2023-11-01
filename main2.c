
#include "src/one.h"


typedef struct Car{
    char *name;
    char *color;
    UniversalGarbage  *garbage;
}Car;

#define CAR 1
Car *newCar();
void Car_set_name(Car*self,const char *name);

void Car_set_color(Car*self,const char *color);
void Car_free(Car *self);

void clear_all(short type, void *value);


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
    Car_set_name(celta,"nome dois");
    Car_set_name(celta,"nome 3");

    printf("nome: %s\n",celta->name);
    printf("cor: %s\n",celta->color);


    UniversalGarbage_free(garbage);
    return 0;
}

Car *newCar(){
    Car *self = UniversalGarbage_create_empty_struct(self, Car);
    self->garbage = newUniversalGarbage(clear_all);
    UniversalGarbage_add_simple_value(self->garbage,self);
    return  self;
}

void Car_set_name(Car*self,const char *name){
    self->garbage->old_value =self->name;
    self->name = UniversalGarbage_add_simple_value(
            self->garbage,
            strdup(name)
    );
}


void Car_set_color(Car*self,const char *color){
    self->garbage->old_value =self->color;
    self->color = UniversalGarbage_add_simple_value(
            self->garbage,
            strdup(color)
    );
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
