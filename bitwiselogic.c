#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct registers {
 int registerInt[50];
 char registerChar [50][10];       
 char type[50][10];
 int intArray[50][intA];
 char charArray[charA][charB];
};
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

int performOperation(struct registers A, int operation);
void printResult(int result, int operation);
void printDisplay(int result, int operation);
int binary(char binaryString[]);
int getRegisterValue();
void variable(char *word[], struct registers *reg, int wordCount);
void functions(struct registers *reg);
 
int main(void) {
    int operation;
    struct registers A;
    int mode;
    printf("Please input 1 for using cpu emulator or 0 for file coding\n");
    scanf("%d", &mode);
    if (mode == 1) {
        A.registerInt[1] = getRegisterValue();
        A.registerInt[2]= getRegisterValue();
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
    } else if (mode == 0) {
        functions(&A);
    }
    return 0;
}

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

int performOperation(struct registers A, int operation) {
    int result = 0;
    switch (operation) {
        case 1: result = A.registerInt[1] & A.registerInt[2]; break;
        case 2: result = A.registerInt[1] | A.registerInt[2]; break;
        case 3: result = A.registerInt[1] ^ A.registerInt[2]; break;
        case 4: result = ~(A.registerInt[1] | A.registerInt[2]); break;
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
            case 1: printf("   \n  |\n  |\n\n"); break;
            case 2: printf(" _ \n _|\n|_ \n\n"); break;
            case 3: printf(" _ \n _|\n _|\n\n"); break;
            case 4: printf("   \n|_|\n  |\n\n"); break;
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
    printf("press 0 for negative value, press 1 for positive, press 2 to quit \n");
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
int str(int a1, char *word[]){
int length = strlen(word[a]);
int  a1 = atoi(&word[a][length - 1]);
return a1;
return length;
}

void variable(char *word[], struct registers *reg, int wordCount) {
    int i  = str(0, word);
    if(strcmp(word[0], "{") ==0){
        condition=1;
    }
    if(strcmp(word[0], "}") ==0){
        condition=0;
    }
    if (strcmp(word[0], "int") == 0 && condition==-1 ||  condition==1) {
        reg->registerInt[i] = atoi(word[2]);
        strcpy(reg->type[i],word[0]);
    }
    if (strcmp(word[0], "char") == 0 && condition==-1 ||  condition==1) {
        strncpy(reg->registerChar[i], word[2])
        strcpy(reg->type[i],word[0]);
    }

     if(strcmp(word[1][lenght-3],"["  ) ==0 && strcmp(word[1][lenght-1],"]"  ) ==0 ){
        char name[50] = word[1];
        for(int b=0;b<4;b++){
            name[length-b]= '\0';
        }
        if(strcmp(word[0],"int")==0){
        intArray[][atoi(word[1][lenght-2])];
        if(strcmp(word[2],"=")==0 ){
        for(int b=0; b<atoi(word[1][lenght-2]);b++){
            intArray[b]= atoi(word[3+b]);
        }
        }
        }
        if(strcmp(word[0],"char")==0){
        charArray[][atoi(word[1][lenght-2])];
        if(strcmp(word[2],"=")==0 ){
        for(int b=0; b<atoi(word[1][lenght-2]);b++){
          strcmp(charArray[b],word[3+b]);
        }
        }
        }
}

    if (strcmp(word[0], "write") == 0 && condition==-1 ||  condition==1) {
        i= str(1,word);
        if (strcmp(reg->type[i], "int") == 0) {
            printf("%d", reg->registerInt[i]);
        } else if (strcmp(reg->type[i], "char") == 0) {
            printf("%s", reg->registerChar[i]);
        }
    }
    if (strcmp(word[0], "read") == 0 && condition==-1 ||  condition==1) {
        i=str(1,word);
        if(strcmp(word[1], "int") == 0 ){
              scanf("%d", &reg->registerInt[i]);
        }
        else if(strcmp(word[1], "char") == 0 ){
        scanf("%s", reg->registerChar[i]);
         }
}
    if(strcmp(word[3], "=") == 0  && condition==-1 ||  condition==1)  {
        registerInt[atoi(&word[4][length - 1]);] = checkCondition(reg->registerInt[atoi(&word[0][length - 1]);], word[2], reg->registerInt[atoi(&word[2][length - 1]);]) ;
}
if(strcmp(word[0],"if")==0  && checkCondition(reg->registerInt[reg1], word[2], reg->registerInt[reg2])){
    condition=1;
}
if(strcmp(word[0],"for")==0){
        while(checkCondition(reg->registerInt[reg1], word[2], reg->registerInt[reg2])) {
            condition=1;
        }
}
if(strcmp(word[i-1], "}")==0){
    condition=0;
}
}
void functions(struct registers *reg) {
    FILE *fptr = fopen("filename.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("Please write limit for string word count: ");
    int x;
    scanf("%d", &x);
    getchar();
    printf("Please write limit for line amount: ");
    int lineLimit;
    scanf("%d", &lineLimit);
    getchar();
    char str[100];
    int lineCount = 0;
    while (fgets(str, sizeof(str), fptr) != NULL && lineCount < lineLimit) {
        str[strcspn(str, "\n")] = '\0'; 

        char **word = malloc(x * sizeof(char *));
        if (word == NULL) {
            printf("Memory allocation failed!\n");
            fclose(fptr);
            return;
        }
        int i = 0;
        char *token = strtok(str, " ");
        while (token != NULL && i < x) {
            word[i] = malloc(strlen(token) + 1); 
            if (word[i] == NULL) {
                printf("Memory allocation failed for word[%d]!\n", i);
                for (int j = 0; j < i; j++) {
                    free(word[j]);
                }
                free(word);
                fclose(fptr);
                return;
            }
            strcpy(word[i], token);
            i++;
            token = strtok(NULL, " ");
        }
        variable(word, reg, i);
        for (int j = 0; j < i; j++) {
            free(word[j]);
        }
        free(word);
        lineCount++;
    }
    fclose(fptr);
}
