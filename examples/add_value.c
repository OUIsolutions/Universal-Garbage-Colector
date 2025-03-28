
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

