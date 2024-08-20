
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

