Hello!
This is a small project on which I am working. The project idea is to create a compiled-to-assembly programming language and a file manager for it. :)

For compiling your code to assembly, you need to run emulator.c file using a C compiler or emulator.exe. But if you want to run the generated assembly, you can run it yourself using NASM x86 assembly or directly run it in the file manager using the run command. :)

In the manual file, the syntax is explained.

"Hello World!" example

section .data

char hello[] = "Hello World!"

void helloWorld() {

    write hello
}

Result: Hello World

Good luck :)
With best wishes and hugs :)

