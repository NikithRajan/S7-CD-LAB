#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MAXPROD 10

char productions[MAXPROD][MAX];
int numProductions = 0;
char input[MAX];
char stack[MAX];
int sp = -1;
int ipPos = 0;

void push(char c){
    stack[++sp] = c;
    stack[sp+1] = '\0';
}

void pop(int n){
    sp -= n;
    if(sp < -1) sp = -1;
    stack[sp+1] = '\0';
}

int matchRHS(const char *rhs){
    int len = strlen(rhs);
    if (sp + 1 < len){
        return 0;
    }
    for(int i = 0 ; i<len ; i++){
        if(stack[sp-len+1+i] != rhs[i]) return 0;
    }
    return 1;
}

int reduce(){
    char action[50];
    for(int p = 0 ; p < numProductions ; p++){
        char lhs = productions[p][0];   // extracts the LHS
        char *rhs = productions[p] + 2; // skips =
        if(matchRHS(rhs)){
            int len = strlen(rhs);
            pop(len);
            push(lhs);

            sprintf(action,"REDUCE: %c ->%s",lhs,rhs);
            printf("%-25s %-25s %-25s\n",stack,input + ipPos , action);
            return 1;
        }
    }
    return 0;
}

int main(){
    printf("Enter the number of productions: ");
    scanf("%d",&numProductions);
    getchar();
    printf("Enter the productions (Eg. E=E+E, E=i):\n");
    for(int i = 0 ; i<numProductions ; i++){
        scanf("%s",productions[i]);
    }
    printf("Enter the input string: ");
    scanf("%s",input);

    printf("\n%-25s %-25s %-25s\n", "STACK","INPUT","ACTION");
    push('$');

    while(input[ipPos] != '\0'){
        char action[50];
        push(input[ipPos]);
        sprintf(action,"SHIFT: %c",input[ipPos]);
        printf("%-25s %-25s %-25s\n",stack,input+ipPos+1,action);
        ipPos++;
        while(reduce());
    }
    while(reduce());
    char startSymbol = productions[0][0];
    if(sp == 1 && stack[sp] == startSymbol && stack[0] == '$')
    printf("\n input string is sucessfully parsed!");
    else
    printf("\n input string is rejected");
    return 0;
}
