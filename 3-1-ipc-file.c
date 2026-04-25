#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    if (fork() == 0) {
        // Child process
        write(fd, "Hello from child process!\n", 27);
        printf("Child wrote to file.\n");
    }   else {
        wait(NULL); // Wait for the child process to finish

        char buffer[28] = {0};
        read(fd, buffer, sizeof(buffer)); // Read the content written by child
        printf("Parent read: %s", buffer);

        write(fd, "Hello from parent process!\n", 28);
        printf("Parent wrote to file.\n");  
    }   

    close(fd);
    return 0;
}