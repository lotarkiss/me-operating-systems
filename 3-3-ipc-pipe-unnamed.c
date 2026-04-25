#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
        int pipefd[2];

        if (pipe(pipefd) == -1) {
                perror("Failed to create pipe");
                exit(-1);
        }

        printf("%d: fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]);

        if (fork() == 0) {
                printf("%d: Child process\n", getpid());
                close(pipefd[1]); // Child only reads

                printf("%d: Checking pipe content\n%d: ", getpid(), getpid());

                // File handling like a pipe
                char buf;
                while (read(pipefd[0], &buf, 1) > 0) {
                        printf("%c", buf);
                }
                printf("\n%d: Closing the reader side of the pipe\n", getpid());

                close(pipefd[0]); // Reader side closed
        }
        else 
        {
                printf("%d: Parent process\n", getpid());
                close(pipefd[0]); // Parent only writes

                printf("%d: Writing to the pipe\n: ", getpid());

                // File handling like a pipe
                char buffer[100];
                strcpy(buffer, "This is a message from the parent process");
                write(pipefd[1], buffer, strlen(buffer));

                close(pipefd[1]); // Writer side closed
                wait(NULL);  // Wait for child to finish
                printf("%d: Parent process is terminating\n", getpid());
        }


        return 0;
}