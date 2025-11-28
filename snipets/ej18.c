#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

void mi_handler() {
    printf("");
}

void mi_handler2() {
    printf("");
}

void mi_handler3() {
    printf("");
}


int main() {
    int fd[2];
    pipe(fd);
    
    pid_t h1_pid = fork();

    if (h1_pid == 0) {
        // h1
        struct stat st;
        close(fd[0]);
        pid_t ppid = getppid();
        signal(SIGINT, mi_handler2);
        signal(SIGHUP, mi_handler3);
        fstat(1, &st);
        print("dejame pensarlo");
    }

    else {
        //padre
        close(fd[1]);
        signal(SIGINT, mi_handler);
    }

}