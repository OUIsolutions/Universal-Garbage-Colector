# Universal-Garbage-Colector
Universal-Garbage is a tiny C library designed to reduce memory leak problems by managing memory allocation and deallocation within scopes.

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
| [Build](/docs/build_and_install.md)| Instructions for building and installing the library |
| [Basic Usage](/docs/basic_usage.md) | Demonstrates the basic usage of the library with a `Car` object example |
| [Add Simple](/docs/add_simple.md) | Shows how to add simple types to the garbage collector |
| [Disconnect](/docs/disconnect.md) | Explains how to disconnect resources from the garbage collector |
| [Resset](/docs/resset.md) | Describes resetting memory for an object |
| [Reallocate](/docs/reallocate.md) | Details how to reallocate memory |
| [Set Return](/docs/set_return.md) | Explains how to handle return values and error management |

# Build Toolchain

* [Darwin](https://github.com/OUIsolutions/Darwin)
* [Silver Chain](https://github.com/OUIsolutions/SilverChain)
* [CAmalgamator](https://github.com/OUIsolutions/CAmalgamator)