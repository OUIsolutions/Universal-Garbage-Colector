## Add Simple
if you dont want to pass the function responsable to release the memory, you can use the UniversalGarbage_add_simple function, that will release the memory of the object passed to it, using the free function.
```c

#include "UniversalGarbageOne.c"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add_simple(garbage,test);
    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}

```
