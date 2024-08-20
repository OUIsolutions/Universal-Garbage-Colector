
#include "../../UniversalGarbage.h"


char * create_list(long size, bool generate_error){
    UniversalGarbage  *garbage = newUniversalGarbage();

    char *final_string = (char*)calloc(1,sizeof(char));
    UniversalGarbage_add_simple_return(garbage, final_string);

    char *new_string = NULL;
    UniversalGarbage_add_simple(garbage, new_string);

    for(int i = 0; i < size; i++){

        new_string  = (char*)calloc(20,sizeof(char));
        UniversalGarbage_resset(garbage, new_string);
        sprintf(new_string,"%d\n",i);

        final_string =(char*)realloc(final_string,
                                     (strlen(final_string)+ strlen(new_string) + 2) *sizeof(char)
        );
        UniversalGarbage_reallocate(garbage,final_string);

        strcat(final_string,new_string);
    }

    if(generate_error){
        UniversalGarbage_free_including_return(garbage);
        return NULL;
    }

    UniversalGarbage_free(garbage);
    return final_string;
}



int main(){

    UniversalGarbage *garbage = newUniversalGarbage();
    char *value_a = create_list(5,false);
    UniversalGarbage_add(garbage,free,value_a);

    char *value_b = create_list(5,true);
    UniversalGarbage_add(garbage,free,value_b);

    printf("value a:\n%s\n",value_a);
    printf("value b:\n%s\n",value_b);

    UniversalGarbage_free(garbage);

    return 0;
}

