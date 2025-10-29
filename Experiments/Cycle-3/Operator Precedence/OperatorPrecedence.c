#include <stdio.h>
#include <string.h>

void main() {
    char stack[20] = {0}, ip[20], opt[10][10][1] = {0}, ter[10];
    int i, j, k, n, top = 0, col, row;

    printf("Enter The No. Of Terminals:\n");
    scanf("%d", &n);
    printf("\nEnter The Terminals:\n");
    scanf("%s", ter);
    printf("\nEnter The Table Values:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf("Enter The Value For %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }

    printf("\n--- OPERATOR PRECEDENCE TABLE ---\n");
    for (i = 0; i < n; i++) printf("\t%c", ter[i]);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("\n%c", ter[i]);
        for (j = 0; j < n; j++) printf("\t%c", opt[i][j][0]);
    }

    stack[top] = '$';
    printf("\n\nEnter The Input String: ");
    scanf("%s", ip);
    i = 0;

    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n\n%s\t\t\t%s\t\t\t\t", stack, ip);

    while (i <= strlen(ip)) {
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) col = k;
            if (ip[i] == ter[k]) row = k;
        }

        if (stack[top] == '$' && ip[i] == '$') {
            printf("String Is Accepted\n");
            break;
        } else if (opt[col][row][0] == '<' || opt[col][row][0] == '=') {
            stack[++top] = opt[col][row][0];
            stack[++top] = ip[i];
            printf("Shift %c", ip[i++]);
        } else if (opt[col][row][0] == '>') {
            while (stack[top] != '<') --top;
            top--;
            printf("Reduce");
        } else {
            printf("\nString Is Not Accepted");
            break;
        }

        printf("\n");
        for (k = 0; k <= top; k++) printf("%c", stack[k]);
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) printf("%c", ip[k]);
        printf("\t\t\t\t");
    }
    getchar();
}
