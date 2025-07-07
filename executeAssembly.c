void executeAssembly(const char* assemblyCode) {
    char system[7];
    #ifdef _WIN32
        void* memory = VirtualAlloc(NULL, strlen(assemblyCode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (memory == NULL) {
            printf("Memory allocation failed\n");
        return;
    }
        memcpy(memory, assemblyCode, strlen(assemblyCode));
        void (*func)() = (void (*)())memory;
        func();
        VirtualFree(memory, 0, MEM_RELEASE);
 }
   #else 
        void* memory = mmap(NULL, strlen(assemblyCode), 
                       PROT_READ | PROT_WRITE | PROT_EXEC,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (memory == MAP_FAILED) {
        printf("Memory allocation failed\n");
        return;
    }
    memcpy(memory, assemblyCode, strlen(assemblyCode));
    void (*func)() = (void(*)())memory;
    func();
    munmap(memory, strlen(assemblyCode));
    } 
#endif