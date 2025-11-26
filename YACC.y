%{
#include <stdio.h>
#include <stdlib.h>

int count_a = 0, count_b = 0;
int yylex(void);
int yyerror(char *s) { return 0; }
%}

%token A B EOL

%%

input:
    /* empty */
  | input line
  ;

line:
    sequence EOL {
        printf((count_a == count_b && count_a > 0) ? "Accepted\n"
                                                  : "Rejected\n");
        count_a = count_b = 0;
    }
  | error EOL {
        printf("Rejected\n");
        count_a = count_b = 0;
    }
  ;

sequence:
    aseq bseq
  ;

aseq:
    A        { count_a++; }
  | aseq A   { count_a++; }
  ;

bseq:
    B        { count_b++; }
  | bseq B   { count_b++; }
  ;

%%

int yylex(void) {
    int c = getchar();
    if (c == 'a') return A;
    if (c == 'b') return B;
    if (c == '\n') return EOL;
    if (c == EOF) return 0;
    return yylex();   // ignore invalid characters
}

int main() {
    printf("Enter strings (a^n b^n, n>0):\n");
    yyparse();
    return 0;
}
