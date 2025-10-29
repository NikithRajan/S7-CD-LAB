%{
    #include "parser.tab.h"    
%}

%%

[a-zA-Z_][a-zA-Z_0-9]* return var;
.                      return yytext[0];
\n                     return 0;

%%
int yywrap(){
    return 1;
}