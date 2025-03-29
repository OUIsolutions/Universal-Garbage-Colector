you use the reallocate function, when you want to change the size of a element, in these way, it you will free the previous value

```c

#include "UniversalGarbageOne.c"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add_simple(garbage,test);
    const char *concatenated_menssage = "new menssage";
    test = (char*)realloc(test, strlen(test) + strlen(concatenated_menssage) + 2);
    UniversalGarbage_reallocate(garbage,test);

    strcat(test,concatenated_menssage);

    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}

```