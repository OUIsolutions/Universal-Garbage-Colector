
#include "UniversalGarbageOne.c"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add_simple(garbage,test);
    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}
