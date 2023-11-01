
#include "src/one.h"


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(NULL);

    char *test = NULL;
    UniversalGarbage_add_simple_value(garbage,(void **)&test);

    test = strdup("sssssssssssssss");
    printf("test %s\n",test);


    UniversalGarbage_free(garbage);
    return 0;
}


