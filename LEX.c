%{
#include <stdio.h>
#include <stdlib.h>
%}

/* Definitions */
DIGIT [0-9]
LETTER [a-zA-Z_]
ID {LETTER}({LETTER}|{DIGIT})*
INT {DIGIT}+
FLOAT {DIGIT}+"."{DIGIT}+
PREPROCESSOR \#[^\n]*

%%

{PREPROCESSOR} { printf("Preprocessor Directive: %s\n", yytext); }

"int"|"float"|"char"|"return"|"if"|"else"|"while"|"for" { printf("Keyword: %s\n", yytext); }

{FLOAT} { printf("Decimal: %s\n", yytext); }

{INT} { printf("Number: %s\n", yytext); }

{ID} { printf("Identifier: %s\n", yytext); }

\"([^\\\"]|\\.)*\" {
    yytext[yyleng - 1] = '\0';  // Null terminate by replacing the closing quote
    printf("String Literal: %s\n", yytext + 1);  // Skip the opening quote and print the string
}


"="|"+"|"-"|"*"|"/"|"%"|"!"|"<"|">" { printf("Operator: %s\n", yytext); }

";"|"{"|"}"|"("|")"|","|"["|"]" { printf("Seperator: %s\n", yytext); }

[ \t\n\r]+  { /* do nothing */ }

%%

int main(int argc,char *argv[]) {

FILE *fp = fopen(argv[1], "r");

yyin = fp;
yylex();
fclose(fp);
return 0;
}
