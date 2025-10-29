%{
    #include "bnf.tab.h"
%}

%%

[0-9]+  {yylval.num = atoi(yytext); return NUMBER;}
[()\*/+-]  {return yytext[0];}
[ \t\n] ;
.       {return yytext[0];}

%%

int yywrap(){
    return 1;
}