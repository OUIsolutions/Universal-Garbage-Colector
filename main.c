
#include "src/one.h"



int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(NULL);

    char *final_string = calloc(1,sizeof(char));
    UniversalGarbage_add_simple_value(garbage,(void**)&final_string);

    char *new_string = NULL;

    for(int i = 0; i < 100; i++){

        new_string  = calloc(20,sizeof(char));
        UniversalGarbage_add_simple_value(garbage,(void**)&new_string);
        sprintf(new_string,"%d\n",i);

        final_string =realloc(final_string,
                   (strlen(final_string)+ strlen(new_string) + 2) *sizeof(char)
        );
        
        strcat(final_string,new_string);
    }

    printf("final %s\n",final_string);
    //printf("size %d\n",garbage->simple_values_size);
    UniversalGarbage_free(garbage);
    return 0;
}

