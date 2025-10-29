#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char trans[20][3][10];
int tcount = 0;

int main(){
    int i , j , k , n , size;
    char states[20][10] , closure[20][10];
    printf("Enter the number of states:");
    scanf("%d",&n);
    printf("Enter the states:\n");
    for(i = 0 ; i<n ; i++){
        scanf("%s",states[i]);
    }
    FILE *fp = fopen("source.txt","r");
    if(!fp) return printf("File Error!\n"),1;
    while (fscanf(fp,"%s %s %s", trans[tcount][0],trans[tcount][1],trans[tcount][2])==3){
        tcount++;
    }
    fclose(fp);

    for(i = 0 ; i<n ; i++){
        size = 1;
        strcpy(closure[0],states[i]); //reflexive property
        for(j = 0 ; j<size ; j++ ){
            for(k = 0 ; k<tcount ; k++){
                if(strcmp(trans[k][0],closure[j])==0 &&  trans[k][1][0] == 'e'){ 
                    int exists = 0;     //checks for duplicates
                    for(int m = 0 ; m<size && !exists ; m++){
                        if(strcmp(closure[m],trans[k][2]) == 0){
                            exists = 1;
                        }
                        if (!exists){
                            strcpy(closure[size++],trans[k][2]);
                        }
                    }
                }

            }
        }
        printf("Epsilon closure of %s = {",states[i]);
        for(j = 0 ; j<size ; j++){
            printf("%s,",closure[j]);
        }
        printf("}\n");
    }
    return 0;

}