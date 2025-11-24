#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char input[100][10];
char stack[100][10];

int tokenCount = 0;
int top = -1;
int i = 0;

void printStep(const char *action)
{
    char st[200] = "";
    char in[200] = "";
    int j = 0;

    for (j = 0; j <= top; j++)
    {
        strcat(st, stack[j]);
    }

    for (j = i; j < tokenCount; j++)
    {
        strcat(in, input[j]);
    }

    strcat(in, "$");

    printf("%-20s %-20s %-20s\n", st, in, action);
}

void push(char *x)
{
    strcpy(stack[++top], x);
}

void pop(int n)
{
    top = top - n;
}

int reduce()
{
    if (top >= 0 && strcmp(stack[top], "id") == 0)
    {
        pop(1);
        push("S");
        printStep("Reduce S->id");
        return 1;
    }

    if (top >= 2 &&
        strcmp(stack[top], ")") == 0 &&
        strcmp(stack[top - 1], "S") == 0 &&
        strcmp(stack[top - 2], "(") == 0)
    {
        pop(3);
        push("S");
        printStep("Reduce S->(S)");
        return 1;
    }

    if (top >= 2 &&
        strcmp(stack[top], "S") == 0 &&
        strcmp(stack[top - 2], "S") == 0 &&
        (strcmp(stack[top - 1], "+") == 0 ||
         strcmp(stack[top - 1], "-") == 0))
    {
        pop(3);
        push("S");
        printStep("Reduce S->S+S");
        return 1;
    }

    return 0;
}

void tokenize(char *expr)
{
    int k = 0;

    while (expr[k] != '\0')
    {
        if (isspace(expr[k]))
        {
            k++;
        }
        else if (strchr("+-()", expr[k]) != NULL)
        {
            input[tokenCount][0] = expr[k];
            input[tokenCount][1] = '\0';
            tokenCount++;
            k = k + 1;
        }
        else if (expr[k] == 'i' && expr[k + 1] == 'd')
        {
            strcpy(input[tokenCount], "id");
            tokenCount++;
            k = k + 2;
        }
        else
        {
            printf("Invalid token: %c\n", expr[k]);
            exit(0);
        }
    }
}

int main()
{
    char expr[100];

    push("$");

    printf("Enter input string: ");
    fgets(expr, 100, stdin);

    expr[strcspn(expr, "\n")] = '\0';

    tokenize(expr);

    printf("\n================== PARSE TABLE ==================\n");
    printf("%-20s %-20s %-20s\n", "STACK", "INPUT", "ACTION");
    printf("-------------------------------------------------\n");

    while (i < tokenCount)
    {
        push(input[i]);
        printStep("Shift");
        i++;

        while (reduce());
    }

    while (reduce());
    
    if (top == 1 && strcmp(stack[1], "S") == 0)
    {
        printStep("ACCEPT");
    }
    else
    {
        printStep("REJECT");
    }

    return 0;
}
