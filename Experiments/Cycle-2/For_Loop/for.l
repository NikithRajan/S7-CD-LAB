%{
#include "for.tab.h"
%}

%%

"for"       { return FOR; }
"("         { return LPAREN; }
")"         { return RPAREN; }
";"         { return SEMICOLON; }
"="         { return ASSIGN; }
"<"         { return LT; }
">"         { return GT; }
"<="        { return LEQ; }
">="        { return GEQ; }
"=="        { return EQ; }
"++"        { return INC; }
"--"        { return DEC; }

[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }

[ \t\n]     ;   /* ignore whitespace */
.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
