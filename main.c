
#include "src/one.h"

void test(void (*callback)(void *value)){

}


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(NULL);

    test((void*)(void*)UniversalGarbage_free);

    
    char *final_string = (char*)calloc(1,sizeof(char));
    UniversalGarbage_add_or_resset_simple_value(garbage, UniversalCast(final_string));

    char *new_string = NULL;

    for(int i = 0; i < 100; i++){

        new_string  = (char*)calloc(20,sizeof(char));
        UniversalGarbage_add_or_resset_simple_value(garbage, UniversalCast(new_string));
        sprintf(new_string,"%d\n",i);

        final_string =(char*)realloc(final_string,
                   (strlen(final_string)+ strlen(new_string) + 2) *sizeof(char)
        );
        UniversalGarbage_reallocate_simple_value(garbage, UniversalCast(final_string));

        strcat(final_string,new_string);
    }

    printf("final %s\n",final_string);
    UniversalGarbage_free(garbage);
    return 0;
}

