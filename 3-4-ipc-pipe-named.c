#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*
  See man 2 mkfifo for more details on how to use pipes for interprocess communication.
*/

int main()
{
        mkfifo("myfifo", 0666); // Create a named pipe (FIFO) with read/write permissions
        printf("%d: Named pipe 'myfifo' created\n", getpid());
        system("ls -l myfifo"); // List the named pipe to verify its creation
        int fd = open("myfifo", O_RDWR);

        printf("%d: fd: %d\n", getpid(), fd);

        if (fork() == 0) {
                printf("%d: Child process\n", getpid());
                close(fd); // Child only reads

                printf("%d: Checking pipe content\n", getpid());

                // File handling like a pipe
                char buf;
                while (read(fd, &buf, 1) > 0) {
                        printf("%c", buf);
                }
                printf("\n%d: Closing the reader side of the pipe\n", getpid());

                close(fd); // Reader side closed
        }
        else 
        {
                printf("%d: Parent process\n", getpid());
                close(fd); // Parent only writes

                printf("%d: Writing to the pipe\n", getpid());

                // File handling like a pipe
                char buffer[100];
                strcpy(buffer, "This is a message from the parent process");
                write(fd, buffer, strlen(buffer));

                close(fd); // Writer side closed
                wait(NULL);  // Wait for child to finish
                printf("%d: Parent process is terminating\n", getpid());
                unlink("myfifo"); // Remove the named pipe after use
                printf("%d: Named pipe 'myfifo' removed\n", getpid());
        }


        return 0;
}