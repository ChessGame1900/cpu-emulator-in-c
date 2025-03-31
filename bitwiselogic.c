#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct registers {
    int register1;
    int register2;
    int register3;
};

int performOperation(struct registers A, int operation);
void printResult(int result, int operation);
void printDisplay(int result, int operation);
int binary(char binaryString[]);

int getRegisterValue() {
    char input[33];
    printf("Enter register value (binary or decimal): \n");
    scanf("%s", input);

    int isBinary = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isBinary = 0;
            break;
        }
    }

    return isBinary ? binary(input) : atoi(input);
}

int main(void) {
    int operation;
    struct registers A;

    A.register1 = getRegisterValue();
    A.register2 = getRegisterValue();

    printf("Enter operation:\n");
    printf("1=AND, 2=OR, 3=XOR, 4=NOR: \n");
    scanf("%d", &operation);

    if (operation >= 1 && operation <= 4) {
        int result = performOperation(A, operation);
        printResult(result, operation);
        printDisplay(result, operation);
    } else {
        printf("Invalid operation!\n");
    }

    return 0;
}
int performOperation(struct registers A, int operation) {
    int result = 0;
    switch (operation) {
        case 1: result = A.register1 & A.register2; break;
        case 2: result = A.register1 | A.register2; break;
        case 3: result = A.register1 ^ A.register2; break;
        case 4: result = ~(A.register1 | A.register2); break;
    }
    return result;
}
void printResult(int result, int operation) {
    switch (operation) {
        case 1: printf("Result of AND: %d\n", result); break;
        case 2: printf("Result of OR: %d\n", result); break;
        case 3: printf("Result of XOR: %d\n", result); break;
        case 4: printf("Result of NOR: %d\n", result); break;
    }
}
void printDisplay(int result, int operation) {
    int digits[10];
    int numDigits = 0;
    int temp = abs(result);
    if (temp == 0) {
        digits[0] = 0;
        numDigits = 1;
    } else {
        while (temp > 0) {
            digits[numDigits] = temp % 10;
            temp /= 10;
            numDigits++;
        }
    }
    if (result < 0) {
        printf(" - ");
    }
    for (int i = numDigits - 1; i >= 0; i--) {
        switch (digits[i]) {
            case 0: printf(" _ \n| |\n|_|\n\n"); break;
            case 1: printf("    \n  |\n  |\n\n"); break;
            case 2: printf(" _ \n _|\n|_ \n\n"); break;
            case 3: printf(" _ \n _|\n _|\n\n"); break;
            case 4: printf("    \n|_|\n  |\n\n"); break;
            case 5: printf(" _ \n|_ \n _|\n\n"); break;
            case 6: printf(" _ \n|_ \n|_|\n\n"); break;
            case 7: printf(" _ \n  |\n  |\n\n"); break;
            case 8: printf(" _ \n|_|\n|_|\n\n"); break;
            case 9: printf(" _ \n|_|\n _|\n\n"); break;
            default: printf("?\n");
        }
    }
}
int binary(char binaryString[]) {
    int decimalValue = 0;
    int length, i, power;
    length = strlen(binaryString);
    for (i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            power = length - i - 1;
            decimalValue += (int)pow(2, power);
        }
    }
    printf("press 0 for negative value, press  1  for positive, press 2 to quit \n");
    int sign;
    scanf("%d", &sign);
    switch (sign) {
        case 0:
            if (decimalValue != 0) {
                decimalValue = ~decimalValue + 1;
            }
            break;
        case 2:
            exit(10);
    }
    return decimalValue;
}
typedef struct {
    char name[50];
    int value;
} Variable;

int variable(char *word[], int wordCount, char *type) {
    int i = 0;
    if (wordCount >= 4 && strcmp(word[0], type) == 0 && atoi(word[2]) >= 0 &&
        (strcmp(word[3], "register1") == 0 || strcmp(word[3], "0x0001") == 0 ||
         strcmp(word[3], "register2") == 0 || strcmp(word[3], "0x0002") == 0 ||
         strcmp(word[3], "register3") == 0 || strcmp(word[3], "0x0003") == 0)) {
        Variable var;
        strcpy(var.name, word[1]);
        var.value = atoi(word[2]);
        printf("Variable: %s = %d\n", var.name, var.value); 
        return 1; 
    }
    return 0; 
}

int functions() {
    char str[100];
    char *token;
    printf("Please write limit for string word count: ");
    int x;
    scanf("%d", &x);
    getchar(); 
    char **word = malloc(x * sizeof(char *)); 
    if (word == NULL) {
        printf("Memory allocation failed!\n");
        return 1; 
    }
    int i = 0;
    printf("Enter a string: ");
    scanf("%99[^\n]", str);
    token = strtok(str, " ");
    while (token != NULL && i < x) {
        word[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    int c;
    for (c = 2; c <= 4; c++) { 
        switch (c) {
            case 2: variable(word, i, "int"); break;
            case 3: variable(word, i, "bool"); break;
            case 4: variable(word, i, "string"); break;
        }
    }
    free(word); 
    return 0;
}
