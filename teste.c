#include "src/declaration.h"

typedef struct Car{
    char *name;
    char *color;
    UniversalGarbage  *garbage;
}Car;

Car *newCar();


void Car_set_name(Car*self,const char *name);


void Car_set_color(Car*self,const char *color);

void Car_free(Car *self);



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
