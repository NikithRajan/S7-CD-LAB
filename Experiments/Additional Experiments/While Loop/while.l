%{
    #include 'while.tab.h'    
%}

%%

"while"     {return WHILE;}
"<"         {return LT;}
">"         {return GT;}
"=="        {return EQ;}
"!="        {return NEQ;}
"<="        {return GEQ;}
">="        {return LEQ;}
"="         {return ASSIGN;}
"("         {return LPAREN;}
")"         {return RPAREN;}
[a-z_A-Z_0-9]   {return ID;}
[0-9]+      {yylval.num = atoi(yytext) ; return NUMBER;}
[ \t\n]     ;
.           {return yytext[0];}

%%

int yywrap(){
    return 1;
}