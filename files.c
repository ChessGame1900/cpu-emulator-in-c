void files(){
    printf("Hello! for choosing writing to blank file ,rewriting file or creating file you need to write: write path, for writing to file : writeA path,  for reading: read path, for printing file : print, for writing to a file : writeText  text" );
    char abc[250];
    scanf("%s", &abc );
    while(abc[0] != '\0'){
        int b= 0;
        char *token = strtok(abc, " ");
        char worda[2][150] ;
        strcpy(worda[b], token);
         token = strtok(NULL, " ");
         b++;
    }
    char inputFile[250];
    strcpy(inputFile, worda[2]);
    if(strcmp(worda[0], "write")==0){
        fopen(inputFile, "w");
    }
    else if(strcmp(worda[0], "read")==0){
        fopen(inputFile, "r");
    }
    else if(strcmp(worda[0], "writeA")==0){
        fopen(inputFile, "a");
    }
    else if(strcmp(worda[0], "print")==0){
        char myString[150];
        while(fgets(myString, 100, fptr)) {
            printf("%s", myString);
        }
        else if(strcmp(worda[0],"writeText")==0){
            char  *a  = strstr(abc, "writeText");
            a= a+9;
            whiile(*a==" "){
                a++;
            }
            char  bx[241];
            strcpy(bx, a, sizeof(bx) - 1);
            a[sizeof(a) - 1] = '\0';
            fprintf(fptr,a);

        }
    }
    else if(strcmp(worda[0], "run")==0){
        char myString[150];
        while(fgets(myString,100,fptr)){
         executeAssembly(myString);
        }
    }
    }

