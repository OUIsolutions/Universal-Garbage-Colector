

# Universal-Garbage-Colector
Universal-Garbage is an tiny C lib for reducing memory leak problems in C
its designed with the idea of releasing all the memory of each scopes once

```c
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

```
# Release
| Item | Description |
| --- | --- |
|[UniversalGarbage.c](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.c)| Definition  | 
|[UniversalGarbage.h](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.h)|Declaration|
|[UniversalGarbageOne.c](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbageOne.c)| One file version|
|[UniversalGarbage.zip](https://github.com/OUIsolutions/Universal-Garbage-Colector/releases/download/3.0.0/UniversalGarbage.zip)| All files|


# Documentation

| Item          | What It Is |
|-------        |-----------|
| [Build](/docs/build_and_install.md)| Build and Install |


# Build Toolchain

* [Darwin](https://github.com/OUIsolutions/Darwin)
* [Silver Chain](https://github.com/OUIsolutions/SilverChain)
* [CAmalgamator](https://github.com/OUIsolutions/CAmalgamator)