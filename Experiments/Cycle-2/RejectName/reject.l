%{
    #include <stdio.h>    
%}

%%

.*hal.*     {printf("Rejected: Conntains hal ");}
.*          {printf("Accepted : %s",yytext);}

%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}