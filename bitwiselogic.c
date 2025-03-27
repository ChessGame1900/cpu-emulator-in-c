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

int main(void) {
    int operation;
    struct registers A;
    char input[33];
    int isBinary = 1;

    printf("Enter register1: \n");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isBinary = 0;
            break;
        }
    }
    A.register1 = isBinary ? binary(input) : atoi(input);

    printf("Enter register2:\n ");
    scanf("%s", input);

    isBinary = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isBinary = 0;
            break;
        }
    }
    A.register2 = isBinary ? binary(input) : atoi(input);

    printf("Enter operation:\n");
    printf("1=AND, 2=OR, 3=XOR, 4=NOR, 5=NOT, 6=SHL, 7=SHR, 8=ADD, 9=subtraction,10=multiplication,11=division\n");
    scanf("%d", &operation);

    if (operation >= 1 && operation <= 11) { 
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
        case 5: result = ~A.register1; break; 
        case 6: result = A.register1 << A.register2; break; 
        case 7: result = A.register1 >> A.register2; break; 
        case 8: result = A.register1 + A.register2; break; 
        case 9: result =  A.register1 - A.register2; break; 
        case 10:result =  A.register1  *A.register2; break; 
         case 11: result =  A.register1 / A.register2; break; 
    }
    return result;
}
void printResult(int result, int operation) {
    switch (operation) {
        case 1: printf("Result of AND: %d\n", result); break;
        case 2: printf("Result of OR: %d\n", result); break;
        case 3: printf("Result of XOR: %d\n", result); break;
        case 4: printf("Result of NOR: %d\n", result); break;
        case 5: printf("Result of NOT: %d\n", result); break;
        case 6: printf("Result of SHL: %d\n", result); break;
        case 7: printf("Result of SHR: %d\n", result); break;
        case 8: printf("Result of  addition: %d\n", result); break;
        case 9: printf("Result of subtraction: %d\n", result); break;
        case 10: printf("Result of multiplication: %d\n", result); break;
        case 11: printf("Result of division: %d\n", result); break;
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
            case 1: printf("  \n |\n |\n\n"); break;
            case 2: printf(" _ \n _|\n|_ \n\n"); break;
            case 3: printf(" _ \n _|\n _|\n\n"); break;
            case 4: printf("  \n|_|\n |\n\n"); break;
            case 5: printf(" _ \n|_ \n _|\n\n"); break;
            case 6: printf(" _ \n|_ \n|_|\n\n"); break;
            case 7: printf(" _ \n |\n |\n\n"); break;
            case 8: printf(" _ \n|_|\n|_|\n\n"); break;
            case 9: printf(" _ \n|_|\n _|\n\n"); break;
            default: printf("?\n");
        }
    }
}
int binary(char binaryString[]) {
    int decimalValue = 0;
    int length = strlen(binaryString);
    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            decimalValue = (decimalValue << 1) | 1;
        } else {
            decimalValue = decimalValue << 1;
        }
    }
    printf("press 0 for negative value, press  1  for positive, press 2 to quit \n");
    int sign;
    scanf("%d", &sign);
    switch (sign) {
        case 0: decimalValue = -1 * decimalValue; break;
        case 2: exit(10);
    }
    return decimalValue;
}
