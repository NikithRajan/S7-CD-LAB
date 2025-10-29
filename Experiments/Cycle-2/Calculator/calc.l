%{
    #include "calc.tab.h"    
    #include <stdio.h>
%}

%%

[0-9]+  {yylval = atoi(yytext); return NUMBER;}
"+"     {return PLUS;}
"-"     {return MINUS;}
"*"     {return MUL;}
"/"     {return DIV;}
"("     {return LPAREN;}
")"     {return RPAREN;}
\n      {return '\n';}
[ \t]   ;
.       {printf("Invalid Character %s",yytext);}
%%

int yywrap(){
    return 1;
}