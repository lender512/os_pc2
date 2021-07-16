#include <stdio.h>
#include <stdlib.h>


void userInput(int memorySize){
    if (memorySize == 0){
        printf("Please enter a valid number\n");
        exit(1);
    }
    else{
        printf("EXIRTO");
    }
}


int main(int argc, char *argv[]){
    char* firstArgument = argv[1];
    userInput(atoi(firstArgument));
    return 0;
}
