
#include "UniversalGarbage.h"


int main(){
    UniversalGarbage *garbage = newUniversalGarbage();

    char *test = strdup("test content");
    UniversalGarbage_add(garbage,free,test);
    printf("test value:%s\n",test);

    UniversalGarbage_free(garbage);
}
