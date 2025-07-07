#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else 
#include <sys/mman.h>
#endif

 int registerInt[50];
 char registerChar [50][10];       
 char type[50][10];
 int checkCondition(int a, const char* op, int b) {
        if (strcmp(op, "==") == 0) return a == b;
        if (strcmp(op, "!=") == 0) return a != b;
        if (strcmp(op, ">") == 0) return a > b;
        if (strcmp(op, "<") == 0) return a < b;
        if (strcmp(op, ">=") == 0) return a >= b;
        if (strcmp(op, "<=") == 0) return a <= b;
        if (strcmp(op, "+") == 0) return a + b;
        if (strcmp(op, "-") == 0) return a - b;
        if (strcmp(op, "*") == 0) return a * b;
        if (strcmp(op, "/") == 0) return a / b;
        return 0;
    }
#include "assemblyCondition.c"

int performOperation();
void printResult(int result, int operation);
void printDisplay(int result, int operation);
int binary(char binaryString[]);
int getRegisterValue();
void variable(char *word[], char*loop);
void functions();

int main(void) {
    int operation;
    int mode;
    printf("Please input 1 for using cpu emulator or 0 for file coding\n");
    scanf("%d", &mode);
    if (mode == 1) {
        registerInt[1] = getRegisterValue();
        registerInt[2]= getRegisterValue();
        printf("Enter operation:\n");
        printf("1=AND, 2=OR, 3=XOR, 4=NOR: \n");
        scanf("%d", &operation);
        if (operation >= 1 && operation <= 4) {
            int result = performOperation(operation);
            printResult(result, operation);
            printDisplay(result, operation);
        } else {
            printf("Invalid operation!\n");
        }
    } else if (mode == 0) {
        functions();
    }
    return 0;
}
#include "binaryOperations.c"

int str(int a, char *word[]){
int length = strlen(word[a]);
int  a1 = atoi(&word[a][length - 1]);
return a1;
}
#include "variable.c"
#include "functions.c"
#include "executeAssembly.c"
#include "files.c"

