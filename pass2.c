#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJ 10

int main() {
    char label[20], opcode[20], operand[20];
    char code[20], mnem[20], sym[20], obj[20];
    int loc, start = 0, progLen = 0, addr, opAddr, found;

    FILE *src = fopen("out.txt","r");
    FILE *opt = fopen("optab.txt","r");
    FILE *symt = fopen("symtab.txt","r");
    FILE *out = fopen("pass2out.txt","w");

    if(!src || !opt || !symt || !out){ printf("File Error\n"); exit(1); }

    fscanf(src, "%s %s %s", label, opcode, operand);

    if(strcmp(opcode,"START")==0) {
        start = strtol(operand,NULL,16);
        fprintf(out,"H^%06s^%06X",label,start);

        char l[20], o[20], op[20];
        int a;
        while(fscanf(src,"%x %s %s %s",&a,l,o,op)!=EOF)
            if(strcmp(o,"END")==0){ 
                progLen = a - start; 
                break; 
            }

        fprintf(out,"^%06X\n",progLen);

        rewind(src);
        fscanf(src,"%s %s %s",label,opcode,operand);
        fscanf(src,"%x %s %s %s",&loc,label,opcode,operand);
    }

    char rec[100][20]; 
    int rc = 0, tStart = loc;

    while(strcmp(opcode,"END")) {

        obj[0] = '\0';
        found = opAddr = 0;

        rewind(opt);
        while(fscanf(opt,"%s %s",code,mnem)!=EOF)
            if(!strcmp(opcode,code)){ found = 1; break; }

        if(found) {
            rewind(symt);
            while(fscanf(symt,"%s %x",sym,&addr)!=EOF)
                if(!strcmp(operand,sym)){ opAddr = addr; break; }

            sprintf(obj,"%s%04X",mnem,opAddr);
        }
        else if(!strcmp(opcode,"WORD")) sprintf(obj,"%06X",atoi(operand));
        else if(!strcmp(opcode,"BYTE")) {
            if(operand[0]=='C')
                for(int i=2;i<strlen(operand)-1;i++){
                    char h[4]; sprintf(h,"%02X",operand[i]); strcat(obj,h);
                }
            else {
                strncpy(obj,operand+2,strlen(operand)-3);
                obj[strlen(operand)-3]='\0';
            }
        }
        else if(!strcmp(opcode,"RESW") || !strcmp(opcode,"RESB")) {

            if(rc){
                fprintf(out,"T^%06X^%02X",tStart,rc*3);
                for(int i=0;i<rc;i++) fprintf(out,"^%s",rec[i]);
                fprintf(out,"\n");
                rc = 0;
            }

            fscanf(src,"%x %s %s %s",&loc,label,opcode,operand);
            tStart = loc;
            continue;
        }

        if(strlen(obj)) {
            strcpy(rec[rc++],obj);

            if(rc==MAX_OBJ) {
                fprintf(out,"T^%06X^%02X",tStart,rc*3);
                for(int i=0;i<rc;i++) fprintf(out,"^%s",rec[i]);
                fprintf(out,"\n");
                rc = 0;
                tStart = loc + 3;
            }
        }

        if(fscanf(src,"%x %s %s %s",&loc,label,opcode,operand)==EOF)
            break;
    }

    if(rc){
        fprintf(out,"T^%06X^%02X",tStart,rc*3);
        for(int i=0;i<rc;i++) fprintf(out,"^%s",rec[i]);
        fprintf(out,"\n");
    }

    rewind(symt);
    while(fscanf(symt,"%s %x",sym,&addr)!=EOF)
        if(!strcmp(operand,sym)) break;

    fprintf(out,"E^%06X\n",addr);

    fclose(src); fclose(opt); fclose(symt); fclose(out);

    printf("Pass 2 completed.\n");
    return 0;
}
