int command_code(const char *s) {
    if (strcmp(s, "section") == 0) return 0;
    if (strcmp(s, "void") == 0)    return 1;
    if (strcmp(s, "int") == 0)     return 2;
    if (strcmp(s, "char") == 0)    return 3;
    if (strcmp(s, "end") == 0)     return 4;
    if (strcmp(s, "write") == 0)   return 5;
    if (strcmp(s, "read") == 0)    return 6;
    if (strcmp(s, "if") == 0)      return 7;
    if (strcmp(s, "for") == 0)     return 8;
    if (strcmp(s, "while") == 0)   return 9;
    if (strcmp(s, "return") == 0)  return 10;
    return -1;
}

void variable(char *word[], char *loop, char *inputFile) {
    char returnType[50][8];
    int ifCondition = 0;
    int forCondition = 0;
    int data = 0;
    int condition = 0;
    char function[50][50];
    int lenght = strlen(word[1]);
    int ba = str(0, word);
    char fileName[100];
    int fi = -1;
    int bd[250][250];

    strcpy(fileName,inputFile);

    FILE *fptr1 = fopen(fileName, "w");
    if (!fptr1) {
        printf("Error opening file\n");
        return;
    }
    fprintf(fptr1, "global _start\n");
    fprintf(fptr1, "_start:\n");
    fprintf(fptr1, "section .text\n");

    int cmd = command_code(word[0]);
    switch (cmd) {
        case 0: // "section"
            // Original: if (strcmp(word[0], "section") == 0 && strcmp(word[1], ".data") == 0)
            if (strcmp(word[1], ".data") == 0) data = 1;
            break;

        case 1: // "void"
        case 2: // "int"
        case 3: // "char"
            // Original: Function declaration or variable declaration
            if (strcmp(word[1], "function") == 0 ) {
                condition = 1;
                fi++;
                fprintf(fptr1,"%s:",word[3]);
                strncpy(function[fi], word[2], sizeof(function[fi]) - 1); 
                strncpy(returnType[fi], word[0], sizeof(returnType[fi]) - 1); 
                if(strcmp(word[3],"(")==0 ){
                  if(strcmp(word[4],"char")==0){
                    fprintf(fptr1, "%s db ""\n", word[5]);
                    int argument= 1;
                  }
                }
                else if(strcmp(word[3][0],"(") ){
                     fprintf(fptr1, "%s dd 0\n", word[5]);
                    int argument= 1;
                 }
            }
            int n=-1;
            // Int variable declaration
            if (cmd == 2 && (data == 1 || condition == 1)) {
                n++;
                bd[n]++; 
                registerInt[bd[n]] = atoi(word[2]);
                fprintf(fptr1, "%s dd %d\n", word[1], registerInt[bd]);
                strcpy(type[bd], word[0]);
            }
            // Char variable declaration
            if (cmd == 3 && (data == 1 || condition == 1)) {
                 n++;
                bd[n]++; 
                strncpy(registerChar[bd], word[2], sizeof(registerChar[bd]) - 1);
                fprintf(fptr1, "%s db '%s'\n", word[1], word[2]); 
                strcpy(type[bd], word[0]);
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
                if (cmd == 2) {
                    fprintf(fptr1, "%s db %s\n", name, value);
                } else if (cmd == 3) {
                    fprintf(fptr1, "%s dd %s\n", name, value);
                }
            }
            break;

        case 4: // "end"
            // Original: if (strcmp(word[0], "end") == 0)
            if (forCondition == 1) {
                fprintf(fptr1, "jmp [%s]\n", loop);
            } else if (ifCondition == 1) {
                fprintf(fptr1, "continue_:\n");
            } else {
                condition = 0;
            }
            break;

        case 5: // "write"
            // Original: if (strcmp(word[0], "write") == 0 && condition == 1)
            if (condition == 1) {
                if (strcmp(type[bd], "int") == 0) {
                    fprintf(fptr1, "mov eax, [%d]\n", registerInt[bd]);
                    fprintf(fptr1, "call print\n");
                } else if (strcmp(type[bd], "char") == 0) {
                    fprintf(fptr1, "mov eax, [%s]\n", registerChar[bd]);
                    fprintf(fptr1, "call print\n");
                }
            }
            break;

        case 6: // "read"
            // Original: if (strcmp(word[0], "read") == 0 && condition == 1)
            if (condition == 1) {
                if (strcmp(type[bd], "int") == 0) {
                    fprintf(fptr1, "call read\n");
                    fprintf(fptr1, "mov [%d], eax\n", registerInt[bd]);
                } else if (strcmp(type[bd], "char") == 0) {
                    fprintf(fptr1, "call read\n");
                    fprintf(fptr1, "mov [%s], eax\n", registerChar[bd]);
                }
            }
            break;

        case 7: // "if"
            // Original: if (strcmp(word[0], "if") == 0 && checkCondition(registerInt[reg1], word[2], registerInt[reg2]))
            if (checkCondition(registerInt[str(1, word)], word[2], registerInt[str(3, word)])) {
                assemblyCondition(registerInt[str(1, word)], word[2], registerInt[str(3, word)], word, fptr1);
                condition = 1;
                ifCondition = 1;
            }
            break;

        case 8: // "for"
            // Original: if (strcmp(word[0], "for") == 0)
            forCondition = 1;
            assemblyCondition(registerInt[str(1, word)], word[2], registerInt[str(3, word)], word, fptr1);
            if (strcmp(word[5], "-") == 0) {
                fprintf(fptr1, "dec %s\n", word[4]);
            } else if (strcmp(word[5], "+") == 0) {
                fprintf(fptr1, "inc %s\n", word[4]);
            }
            condition = 1;
            break;

        case 9: // "while"
            // Original: if (strcmp(word[0], "while") == 0)
            forCondition = 1;
            assemblyCondition(registerInt[str(1, word)], word[2], registerInt[str(3, word)], word, fptr1);
            condition = 1;
            break;

        case 10: // "return"
            // Original: if (strcmp(word[0], "return") == 0)
            {
                int returnInt[250];
                char returnChar [250][250];
                if (strcmp(returnType[fi], "int") == 0) {
                    int b = 0;
                    if (strcmp(word[1], "0") != 0 && atoi(word[1]) != 0) {
                        returnInt[b] = registerInt[atoi(&word[1][lenght])];
                    } else {
                        returnInt[b] = atoi(word[1]);
                    }
                } else if (strcmp(returnType[fi], "char") == 0) {
                    int b = 0;
                    if (atoi(&word[1][lenght - 1]) <= 0 && word[1][lenght - 1] != '0') { 
                        strncpy(returnChar[b], word[1], sizeof(returnChar[b]) - 1);
                    }
                }
            }
            break;

        default:
            break;
    }

    // Assignment (outside switch to match original logic)
    if (word[3] && strcmp(word[3], "=") == 0 && condition == 1) {
        assemblyCondition(registerInt[], word[2], registerInt[]);
    }
    // Function call (outside switch)
    if (fi >= 0 && strcmp(word[0], function[fi]) == 0 && strcmp(word[1], "()") == 0) {
        if (strcmp(returnType[fi], "void") == 0) {
            printf("void function can't return :(");
        } else if (strcmp(returnType[fi], "int") == 0) {
            fprintf(fptr1,"call %s",function[fi]);
        } else if (strcmp(returnType[fi], "char") == 0) {
            fprintf(fptr1,"call %s",function[fi]);
        }
    }
    fclose(fptr1);
    printf("Assembly code written to %s\n",fileName);
}
