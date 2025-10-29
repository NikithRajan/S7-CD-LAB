#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char input[50];
int inputptr = 0;
char derivation[100] , temp[100];
int n = 0;

void Expression();
void ExpressionPrime();
void Term();
void TermPrime();
void Factor();
void advance();

void advance(){
    inputptr++;
}

void Expression(){
    strcpy(derivation,"TE'");
    printf("E = %-25s",derivation);
    printf("E -> TE'\n");
    Term();
    ExpressionPrime();
}

void ExpressionPrime(){
    int i , n = 0, len;
    for(i = 0 ; i<strlen(derivation) ; i++){
        if(derivation[i] != 'e')
        temp[n++] = derivation[i];
    }
    temp[n] = '\0';
    strcpy(derivation,temp);
    len = strlen(derivation);

    for(n = 0; n<len && derivation[n] != 'E' ; n++);
        
    if(input[inputptr] == '+'){
    
        i = n+2;
        while(i<=len){
            derivation[i+2] = derivation[i];
            i++;
        }

        derivation[n++] = '+';
        derivation[n++] = 'T';
        derivation[n++] = 'E';
        derivation[n++] = '\'';
        derivation[len+3] = '\0';

        printf("E = %-25s", derivation);
        printf("E' -> +TE'\n");

        advance();
        Term();
        ExpressionPrime();
        

    }
    else{
        derivation[n] = 'e';
        derivation[n+1] = '\0';
        printf("E = %-25s",derivation);
        printf("E' -> e\n");
    }
    
}

void Term(){
    int i , n = 0 , len;
    for(i = 0 ; i<strlen(derivation); i++){
        if(derivation[i] != 'e'){
            temp[n++] = derivation[i];
        }

    }
    temp[n] = '\0';
    strcpy(derivation,temp);
    len = strlen(derivation);

    for(n = 0 ; n<len && derivation[n] != 'T'; n++);
    i = n+1;
    while(i<len){
        derivation[i+2] = derivation[i];
        i++;
    }
    derivation[i++] = 'F';
    derivation[i++] = 'T';
    derivation[i++] = '\'';
    derivation[len+3] = '\0';

    printf("E = %-25s",derivation);
    printf("T->FT'\n");

    Factor();
    TermPrime();
}

void TermPrime(){
    int i ,n = 0, len;
    for(i = 0 ; i<strlen(derivation) ; i++){
        if (derivation[i] != 'e')
            temp[n++] = derivation[i];
    }
    temp[n] = '\0';
    strcpy(derivation,temp);
    len = strlen(derivation);

    for(n = 0 ; n<len && derivation[n] != 'T' ; n++);
    if(input[inputptr] == '*'){
        i = n+2;
        while(i<len){
            derivation[i+2] = derivation[i];
            i++; 
        }
        derivation[i++] = '*';
        derivation[i++] = 'F';
        derivation[i++] = 'T';
        derivation[i++] = '\'';
        derivation[len+3] = '\0';

        printf("E = %-25s",derivation);
        printf("T' -> *FT'\n");
        advance();
        Factor();
        TermPrime();
    }
    else{
        derivation[n] = 'e';
        derivation[n+1] = '\0';
        printf("E = %-25s",derivation);
        printf("T' -> e\n");
    
    }
}

void Factor(){
    int i  , n = 0 , len;
    for(i = 0 ; i<strlen(derivation); i++){
        if (derivation[i] != 'e'){
            temp[n++] = derivation[i];
        }
    }
    temp[n] = '\0';
    strcpy(derivation,temp);
    len = strlen(derivation);

    for(n = 0 ; n<len && derivation[n] != 'F' ; n++);

    if(input[inputptr] == 'i' || input[inputptr] == 'I'){
        derivation[n] = 'i';
        derivation[n+1] = '\0';
        printf("E = %-25s",derivation);
        printf("F-> i\n");
        advance();
    }
    else if(input[inputptr] == '('){
        advance();
        Expression();
        if(input[inputptr] == ')'){
            advance();
            derivation[i++] = '(';
            derivation[i++] = 'E';
            derivation[i++] = ')';
            derivation[i++] = '\0';
            printf("E = %-25s",derivation);
            printf("F -> (E)\n");
        }
        else{
            printf("\nSyntax Error : Missing ')'\n");
        }
    }
    else{
        printf("\n Syntax Error : Invalid Factor\\n");
        exit(1);
    }
}

int main(){
    printf("\nGrammar without left recursion:\n");
    printf("\tE  -> TE'\n");
    printf("\tE' -> +TE' | e\n");
    printf("\tT  -> FT'\n");
    printf("\tT' -> *FT' | e\n");
    printf("\tF  -> (E) | i\n");
    printf("Enter the input expression");
    scanf("%s",input);
    printf("\nDerivation:\n");
    printf("E\n");
    Expression();
    printf("Parsing Completed Succesfully!!");
    return 0;
}



