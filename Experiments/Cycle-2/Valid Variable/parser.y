%{
    #include <stdio.h>
    extern int yylex();
    extern int yyerror(const char *);
    int valid = 1;    
%}

%token var

%%

start : var

%%

int yyerror(const char *s){
    printf("\n Not a valid identifier");
    valid = 0;
    return 0;
}

int main(){
    printf("\n Enter a name to test the variable");
    yyparse();
    if(valid){
        printf("its a valid variable");
    }
    return 0;
}