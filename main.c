
#include "src/one.h"


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage();
    char * value_a = strdup("test");


    UniversalGarbage_free(garbage);
}

