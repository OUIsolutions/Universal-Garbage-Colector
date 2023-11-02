
#include "src/one.h"


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage();
    char * value_a = strdup("test a");
    UniversalGarbage_add_simple(garbage,value_a);

    char * value_b = strdup("test b");
    UniversalGarbage_add_simple(garbage,value_b);

    char * value_c = strdup("test c");
    UniversalGarbage_add_simple(garbage,value_c);

    printf("value a :%s\n",value_a);
    printf("value b :%s\n",value_b);
    printf("value c :%s\n",value_c);
    free(value_a);
    UniversalGarbage_free(garbage);

}

