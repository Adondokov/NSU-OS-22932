#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[]) {
//    printf("\n%d %s\n", argc, argv[0]);
    if(argc < 2){
        perror("You must at least enter program name to exec\n");
        exit(1);
    }
    pid_t pid = fork();
    if(pid == 0){
        printf("Child process has been created successfully\n");
        execvp(argv[1], argv + 1);
    } else if(pid == -1) perror("fork err");
    else {
        int exit_status;
        pid_t exited_pid = waitpid(pid, &exit_status, 0);
        if(exited_pid == pid){
            if (WIFEXITED(exit_status)) printf("\nDefault exit , status is:%d", WEXITSTATUS(exit_status));
            if (WIFSIGNALED(exit_status)) printf("\nKilled by signal=%d%s", WTERMSIG(exit_status), WCOREDUMP(exit_status) ? " (dumped core)" : "");
            if (WIFSTOPPED(exit_status)) printf("\nStopped by signal=%d", WSTOPSIG(exit_status));
            if (WIFCONTINUED(exit_status)) printf("\nContinued");
            printf("\n");
        }
    }
    printf("Last msg from parent process\n");
    return 0;
}
