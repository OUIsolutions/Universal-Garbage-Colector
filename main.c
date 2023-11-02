
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
    if(error){
        UniversalGarbage_free_including_return(garbage);
        return NULL;
    }

    UniversalGarbage_free(garbage);
    return final_string;
}



int main(){
    char *test_correct = create_list(100,false);
    printf("correct %s",test_correct);
    free(test_correct);

    char *test_incorrect = create_list(100,true);
    if(!test_incorrect){
        printf("incorrect is NULL\n");
    }

    return 0;
}

