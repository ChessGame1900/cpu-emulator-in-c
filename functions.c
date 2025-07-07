int functions() {
    char inputFile[250];
    scanf("%s", inputFile );
    FILE *fptr = fopen(inputFile, "r");
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
        variable(word,loop);
        for (int j = 0; j < i; j++) {
            char  saved[50][100];
            strcpy(saved[j][i], word);
            free(word[j]);
        }
        lineCount++;
    }
    free(word);
    fclose(fptr);
    variable(word,loop);
    printf("File processed successfully.\n");
    return fptr;
}