#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 1000

char keywords[6][10]={"int", "float", "while", "for", "return", "void"};

int isKeyword(const char *word){
for(int i=0;i<6;i++)
if(strcmp(word,keywords[i])==0)
return 1;
return 0;
}


void main(){
char token[100],line[MAX];
FILE *file = fopen("input.txt","r");
int i=0,j=0;
while(fgets(line,sizeof(line),file)){
i = 0;
j = 0;


while(isspace(line[i]))i++;

if(line[i]=='#'){
printf("Preprocessor directive\t\t:%s",line);
continue;
}

while(line[i]!='\0' && line[i]!='\n'){
char ch = line[i];
    if(ch=='"'){
    i++;
    j=0;
    while(line[i]!='"' && line[i]!='\0' && line[i]!='\n'){
    token[j++]=line[i++];
    }
    token[j]='\0';
    printf("\nString Literal\t\t:\"%s\"",token);
    if(line[i]=='"')i++;
    j=0;
    continue;
    }

if(isalnum(ch) || ch=='.' || ch=='_'){
token[j++]=ch;
}
else{
if(j>0){
token[j]='\0';
if(isKeyword(token))printf("\nKeyword\t\t\t:%s",token);
else if(isdigit(token[0]))printf("\nNumber\t\t\t:%s",token);
else printf("\nIdentifier\t\t:%s",token);
j=0;
}

if(strchr("*/+-=",ch)) printf("\nOperator\t\t:%c",ch);
else if (strchr("(){}[];,",ch)) printf("\nSeparator\t\t:%c",ch);
}

i++;
}


if(j>0){
token[j]='\0';
if(isKeyword(token))printf("\nKeyword\t\t:%s",token);
else if(isdigit(token[0]))printf("\nNumber\t\t:%s",token);
else printf("\nIdentifier\t\t:%s",token);
}
}


fclose(file);
}




