
#include "src/one.h"

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
    UniversalGarbage_add(self->garbage, free, self->color);
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
    UniversalGarbage  *garbage = newUniversalGarbage();
    Car  *test = newCar();
    UniversalGarbage_add(garbage,Car_free,test);
    Car_set_name(test,"ferrari");
    Car_set_color(test,"red");

    printf("model:%s\n",test->name);
    printf("color:%s\n",test->color);

    UniversalGarbage_free(garbage);
}

