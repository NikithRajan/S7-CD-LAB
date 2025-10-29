%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%union {
    int num;
    char *str;
}

%token FOR LPAREN RPAREN LEQ GEQ ASSIGN INC DEC LT GT EQ SEMICOLON
%token <str> ID
%token <num> NUMBER

%right ASSIGN
%left EQ
%left LT GT LEQ GEQ
%left INC DEC

%%

stmt : FOR LPAREN assgn SEMICOLON comp SEMICOLON exp_opr RPAREN {
    printf("Valid FOR statement syntax\n");
}
;

assgn : ID ASSIGN var;

comp : var relop var;

relop : LT 
      | GT 
      | LEQ 
      | GEQ 
      | EQ
      ;

var : ID 
    | NUMBER
    ;

exp_opr : /* empty */
        | expr
        ;

expr : ID ASSIGN expr
     | ID
     | NUMBER
     | expr LT expr
     | expr GT expr
     | expr LEQ expr
     | expr GEQ expr
     | expr EQ expr
     | ID INC
     | ID DEC
     ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter a FOR statement: ");
    yyparse();
    return 0;
}
