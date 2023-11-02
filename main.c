
#include "src/one.h"


char * create_list(long size, bool error){
    UniversalGarbage  *garbage = newUniversalGarbage();

    char *final_string = (char*)calloc(1,sizeof(char));
    UniversalGarbage_set_return(garbage, free, final_string);

    char *new_string = NULL;
    UniversalGarbage_add(garbage, free, new_string);

    for(int i = 0; i < 100; i++){

        new_string  = (char*)calloc(20,sizeof(char));
        UniversalGarbage_resset(garbage, new_string);
        sprintf(new_string,"%d\n",i);

        final_string =(char*)realloc(final_string,
                                     (strlen(final_string)+ strlen(new_string) + 2) *sizeof(char)
        );
        UniversalGarbage_reallocate(garbage,final_string);

        strcat(final_string,new_string);
    }
    printf("%s",final_string);
    UniversalGarbage_free(garbage);

}



int main(){

    return 0;
}

