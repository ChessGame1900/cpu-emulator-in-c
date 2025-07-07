
static char* assemblyCondition(int a, const char*op  , int b, char **word, FILE *fptr1){
    static char loop[20];
         if (strcmp(op, "==") == 0) {
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "je equal_");
        fprintf(fptr1, "equal_: ");
        strcpy(loop, "equal_");
         }
        if (strcmp(op, "!=") == 0){
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "jne notEqual_");
        fprintf(fptr1, "notEqual_: ");
         strcpy(loop, "notEqual_");
        }
        if (strcmp(op, ">") == 0){
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "jg greater_");
        fprintf(fptr1, "greater_: ");
        strcpy(loop, "greater_");
        }
        if (strcmp(op, "<") == 0) {
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "jl less_");
        fprintf(fptr1, "less_: ");
        strcpy(loop, "less_");
        }
        if (strcmp(op, ">=") == 0){
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "jge  greaterOrEqual_");
        fprintf(fptr1, "greaterOrEqual_: ");
        strcpy(loop, "greaterOrEqual_");
        }
        if (strcmp(op, "<=") == 0) {
        fprintf(fptr1, "cmp dword [%s], [%s]", word[0], word[2]);
        fprintf(fptr1, "jle lessOrEqual_");
        fprintf(fptr1, "less_: ");
         strcpy(loop, "lessOrEqual_");
        }
        if (strcmp(op, "+") == 0) {
         fprintf(fptr1, "mov eax, [%s]", word[0]);
        fprintf(fptr1, "mov ebx, [%s]", word[2]);
         fprintf(fptr1, "add eax, ebx");
         fprintf(fptr1, "mov [%s], eax", word[4]);
        }
        if (strcmp(op, "-") == 0) {
        fprintf(fptr1, "mov eax, [%s]", word[0]);
        fprintf(fptr1, "mov ebx, [%s]", word[2]);
         fprintf(fptr1, "sub eax, ebx");
         fprintf(fptr1, "mov [%s], eax", word[4]);
        }
        if (strcmp(op, "*") == 0){
        fprintf(fptr1, "mov eax, [%s]", word[0]);
        fprintf(fptr1, "mov ebx, [%s]", word[2]);
         fprintf(fptr1, "imul eax, ebx");
         fprintf(fptr1, "mov [%s], eax", word[4]);
        }
        if (strcmp(op, "/") == 0) {
        fprintf(fptr1, "mov eax, [%s]", word[0]);
        fprintf(fptr1, "mov ebx, [%s]", word[2]);
         fprintf(fptr1, "xor edx, edx");
         fprintf(fptr1, "idiv ebx");
          fprintf(fptr1, "mov [%s], eax", word[4]);
        }
        return loop;
}