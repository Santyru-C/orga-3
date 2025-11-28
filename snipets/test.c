#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <signal.h>

void mi_handler() {
    printf("");
}

int main() {
    printf("hola\n");
    sleep(1);
    signal(SIGINT, mi_handler);
    char* cadena;
    cadena = (char *) malloc(sizeof(char) * 5);
    free(cadena);
    return 1;
}