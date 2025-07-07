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

int performOperation(int operation) {
    int result = 0;
    switch (operation) {
        case 1: result = registerInt[1] & registerInt[2]; break;
        case 2: result = registerInt[1] | registerInt[2]; break;
        case 3: result = registerInt[1] ^ registerInt[2]; break;
        case 4: result = ~(registerInt[1] | registerInt[2]); break;
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