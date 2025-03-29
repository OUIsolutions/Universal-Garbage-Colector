you use the resset function, when you want to add a new value
to a element, in these way, it you will free the previous value

```c


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


```