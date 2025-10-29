#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "bool", "true", "false",
    "class", "public", "private", "protected", "namespace", "using"
};

int isKeyword(char *str){
    if(str == NULL){
        return 0;
    }
    int arraySize = sizeof(keywords)/sizeof(keywords[0]);
    for(int i = 0 ; i<arraySize ; i++){
        if(strcmp(str,keywords[i])==0) return 1;
    }
    return 0;
}

int isDelimiter(char ch){
    return (ch ==';'|| ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']');
}

int isOperator(char ch){
     return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '!' ||
            ch == '&' || ch == '|' || ch == '%' || ch == '^' ||
            ch == '~' || ch == '?' || ch == ':');
}

void skipSingleLineComments(FILE *fp){
    int ch;
    while((ch = fgetc(fp))!= EOF && ch != '\n'){}
    if(ch == '\n') ungetc(ch,fp);
}

void skipMultiLineCommments(FILE *fp){
    int ch , prev = 0;
    while((ch = fgetc(fp)) != EOF){
        if (prev == '*' && ch == '/'){
            break;
        }
        prev = ch;
    }
}
void lexicalAnalyzer(FILE *fp){
    int c;
    char buffer[MAX];
    int i;
    int tokenCount = 0;

    while((c = fgetc(fp)) != EOF){
        char ch = (char)c;
        if(isspace(ch)){
            continue;
        }
        if(isalpha(ch) || ch == '_'){ // Identifiers & Keywords
            i = 0;
            buffer[i++] = ch;
            int next_c;
            while(i<MAX -1 && (next_c = fgetc(fp))!=EOF){
                char next_ch = (char)next_c;
                if(isalnum(next_ch) || next_ch == '_'){
                    buffer[i++] = next_ch;
                }
                else{
                    ungetc(next_c,fp);
                    break;
                }
            }
            buffer[i] = '\0';
            if(isKeyword(buffer)){
                printf("<KEYWORD , %s>\n",buffer);
            }
            else{
                printf("<IDENTIFIER, %s>\n",buffer);
            }
            tokenCount++;
        }

        else if(isdigit(ch)){
            i = 0;
            buffer[i++] = ch;
            int hasDot = 0;
            int next_c;
            while(i<MAX -1 && (next_c = fgetc(fp))!= EOF){
                char next_ch = (char) next_c;
                if(isdigit(next_ch)){
                    buffer[i++] = next_ch;
                }
                else if(next_ch == '.' && !hasDot){
                    hasDot = 1;
                    buffer[i++] = next_ch;
                }
                else{
                    ungetc(next_c,fp);
                    break;
                }

            }
            buffer[i] = '\0';
            printf("<NUMBER : %s>\n",buffer);
            tokenCount++;
        }
        else if(ch == '"'){
            i = 0;
            buffer[i++] = ch;

            int next_c;
            while(i<MAX - 1 && (next_c = fgetc(fp))!= EOF){
                char next_ch = (char)next_c;
                if(next_ch == '"'){
                    break;
                }
                else if(next_ch == '\\'){
                    if(i<MAX - 1 && (next_c = fgetc(fp))!= EOF){
                        buffer[i++] = (char)next_c;
                    }
                }
            }
            buffer[i] = '\0';
            printf("<STRING, %s>\n",buffer);
            tokenCount++;
        }
        else if(isOperator(ch)){
            int i = 0;
            int next_c;
            if(next_c !=EOF){
                char next = (char)next_c;
                if ((ch == '=' && next == '=') || 
                    (ch == '!' && next == '=') ||
                    (ch == '<' && next == '=') ||
                    (ch == '>' && next == '=') ||
                    (ch == '&' && next == '&') ||
                    (ch == '|' && next == '|') ||
                    (ch == '+' && next == '+') ||
                    (ch == '-' && next == '-') ||
                    (ch == '+' && next == '=') ||
                    (ch == '-' && next == '=') ||
                    (ch == '*' && next == '=') ||
                    (ch == '/' && next == '=') ||
                    (ch == '%' && next == '=') ||
                    (ch == '<' && next == '<') ||
                    (ch == '>' && next == '>') ||
                    (ch == '-' && next == '>')) {
                        printf("<OPERATOR, %c%c>\n", ch, next);
                    }
                    else{
                        ungetc(next_c,fp);
                        printf("<OPERATOR,%c>\n",ch);
                    }
            }
            else{
                printf("<OPERATOR,%c>\n",ch);
            }
            tokenCount++;
        }
        else if(isDelimiter(ch)){
            printf("<DELIMITER, %c>\n",ch);
            tokenCount++;
        }
    }
    printf("The total token processed : %d",tokenCount);
}

int main(){
    FILE *fp;
    fp = fopen("source.txt","r");
    printf("Tokens Identified:\n");
    lexicalAnalyzer(fp);
    fclose(fp);
    return 0;

}