
#include "src/one.h"


int main(){
    UniversalGarbage  *garbage = newUniversalGarbage(NULL);

    char *final_string = NULL;
    for(int i = 0; i < 100; i++){

        char *new_string = NULL;

        if(final_string){
            new_string  = calloc(strlen(final_string) + 20,sizeof(char));
            UniversalGarbage_add_simple_value(garbage,new_string);
            sprintf(new_string,"%s%d\n",final_string,i);
        }

        if(!final_string){
            new_string= calloc(20,sizeof(char));
            UniversalGarbage_add_simple_value(garbage,new_string);
            sprintf(new_string,"%d\n",i);
        }

        final_string = new_string;

        UniversalGarbage_add_simple_value(garbage,new_string);

    }
    printf("final %s\n",final_string);
    UniversalGarbage_free(garbage);
    return 0;
}


