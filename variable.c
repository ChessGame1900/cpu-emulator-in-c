
void variable(char *word[], char *loop) {
    char returnType[8] = ""; 
    int ifCondition = 0;
    int forCondition = 0;
    int data = 0;
    int condition = 0;
    char function[50] = "";
    int lenght = strlen(word[1]);
    int ba = str(0, word);

    FILE *fptr1 = fopen("filename.asm", "w");
    if (!fptr1) {
        printf("Error opening file\n");
        return;
    }
    fprintf(fptr1, "global _start\n");
    fprintf(fptr1, "_start:\n");
    fprintf(fptr1, "section .text\n");

    if (strcmp(word[0], "section") == 0 && strcmp(word[1], ".data") == 0) {
        data = 1;
    }

    // Function declaration
    if (strcmp(word[0], "void") == 0 || strcmp(word[0], "int") == 0 || strcmp(word[0], "char") == 0) {
        condition = 1;
        strncpy(function, word[2], sizeof(function) - 1); 
        strncpy(returnType, word[0], sizeof(returnType) - 1); 
    }
    if (strcmp(word[0], "end") == 0) {
        if (forCondition == 1) {
            fprintf(fptr1, "jmp [%s]\n", loop);
        } else if (ifCondition == 1) {
            fprintf(fptr1, "continue_:\n");
        } else {
            condition = 0;
        }
    }

    // Int variable declaration
    if (strcmp(word[0], "int") == 0 && (data == 1 || condition == 1)) {
        registerInt[ba] = atoi(word[2]);
        fprintf(fptr1, "%s dd %d\n", word[1], registerInt[ba]);
        strcpy(type[ba], word[0]);
    }

    // Char variable declaration
    if (strcmp(word[0], "char") == 0 && (data == 1 || condition == 1)) {
        strncpy(registerChar[ba], word[2], sizeof(registerChar[ba]) - 1);
        fprintf(fptr1, "section .data\n");
        fprintf(fptr1, "%s db '%s'\n", word[1], word[2]); 
        strcpy(type[ba], word[0]);
    }

    // Array declaration (int or char)
    if (word[1][lenght-3] == '[' && word[1][lenght-1] == ']' && (data == 1 || condition == 1)) {
        char name[50];
        strncpy(name, word[1], lenght-3); 
        name[lenght-3] = '\0'; 
        int val = atoi(&word[1][lenght-2]);
        char value[256] = ""; 
        for (int bx = 0; bx <= val; bx++) {
            strcat(value, word[bx]);
            if (bx < val) strcat(value, ",");
        }
        if (strcmp(word[0], "int") == 0) {
            fprintf(fptr1, "%s db %s\n", name, value);
        } else if (strcmp(word[0], "char") == 0) {
            fprintf(fptr1, "%s dd %s\n", name, value);
        }
    }

    // Write function
    if (strcmp(word[0], "write") == 0 && condition == 1) {
        ba = str(1, word);
        if (strcmp(type[ba], "int") == 0) {
            fprintf(fptr1, "mov eax, [%d]\n", registerInt[ba]);
            fprintf(fptr1, "call print\n");
        } else if (strcmp(type[ba], "char") == 0) {
            fprintf(fptr1, "mov eax, [%s]\n", registerChar[ba]);
            fprintf(fptr1, "call print\n");
        }
    }

    // Read function
    if (strcmp(word[0], "read") == 0 && condition == 1) {
        ba = str(1, word);
        if (strcmp(type[ba], "int") == 0) {
            fprintf(fptr1, "call read\n");
            fprintf(fptr1, "mov [%d], eax\n", registerInt[ba]);
        } else if (strcmp(type[ba], "char") == 0) {
            fprintf(fptr1, "call read\n");
            fprintf(fptr1, "mov [%s], eax\n", registerChar[ba]);
        }
    }

    // Assignment
    if (word[3] && strcmp(word[3], "=") == 0 && condition == 1) {
        assemblyCondition(registerInt[atoi(&word[0][lenght - 1])], word[2], registerInt[atoi(&word[2][lenght - 1])], word, fptr1);
    }
    int reg1 = str(1, word);
    int reg2 = str(3, word);

    if (strcmp(word[0], "if") == 0 && checkCondition(registerInt[reg1], word[2], registerInt[reg2])) {
        assemblyCondition(registerInt[reg1], word[2], registerInt[reg2], word, fptr1);
        condition = 1;
        ifCondition = 1;
    }

    if (strcmp(word[0], "for") == 0) {
        forCondition = 1;
        assemblyCondition(registerInt[reg1], word[2], registerInt[reg2], word, fptr1);
        if (strcmp(word[5], "-") == 0) {
            fprintf(fptr1, "dec %s\n", word[4]);
        } else if (strcmp(word[5], "+") == 0) {
            fprintf(fptr1, "inc %s\n", word[4]);
        }
        condition = 1;
    }

    if (strcmp(word[0], "while") == 0) {
        forCondition = 1;
        assemblyCondition(registerInt[reg1], word[2], registerInt[reg2], word, fptr1);
        condition = 1;
    }
    int returnInt[250];
    char returnChar [250][250];
    if (strcmp(word[0], "return") == 0) {
        if (strcmp(returnType, "int") == 0) {
            int b = 0;
            if (strcmp(word[1], "0") != 0 && atoi(word[1]) == 0) {
                returnInt[b] = registerInt[atoi(&word[1][lenght - 1])];
            } else {
                returnInt[b] = atoi(word[1]);
            }
        } else if (strcmp(returnType, "char") == 0) {
            int b = 0;
            if (atoi(&word[1][lenght - 1]) <= 0 && word[1][lenght - 1] != '0') { 
                strncpy(returnChar[b], word[1], sizeof(returnChar[b]) - 1);
            }
        }
    }
    char save[50][50] = {0};
    if (ba > 1 && strcmp(word[ba - 1], "s") == 0) { 
        for (int b1 = 0; b1 < ba - 1; b1++) {
            strcpy(save[b1], word[b1]);
        }
    }
    if (strcmp(word[0], "save") == 0 && word[0][lenght - 1] == 's'){
        variable(save[lenght - 2], loop);
    }

    if (strcmp(word[0], function) == 0 && strcmp(word[0], "()") == 0) {
        if (strcmp(returnType, "void") == 0) {
            fprintf(fptr1, "mov eax, %s\n", "void function can't return :(");
            fprintf(fptr1, "call print\n");
            variable(save, loop);
        } else if (strcmp(returnType, "int") == 0) {
            fprintf(fptr1, "mov eax, %d\n", returnInt[0]);
            fprintf(fptr1, "call print\n");
            variable(save, loop);
        } else if (strcmp(returnType, "char") == 0) {
            fprintf(fptr1, "mov eax, %s\n", returnChar[0]);
            fprintf(fptr1, "call print\n");
            variable(save, loop);
        }
    }
    fclose(fptr1);
    printf("Assembly code written to filename.asm\n");
}