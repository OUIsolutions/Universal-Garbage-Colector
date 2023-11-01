
#include "src/one.h"


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(NULL);

    char *test = strdup("aaaaaaaa");
    UniversalGarbage_add_simple_value(garbage,(void **)&test);
    printf("test %s\n",test);

    UniversalGarbage_free(garbage);
    return 0;
}


