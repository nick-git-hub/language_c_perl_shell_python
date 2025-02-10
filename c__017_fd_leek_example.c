#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    off_t offset;
    char buffer[20];
    ssize_t bytesRead;

    fd = open("data/3.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // use lseek move fd to number 10 char
    offset = lseek(fd, 10, SEEK_SET);
    if (offset == -1) {
        perror("Error using lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // star from 10 char read 20 char
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    system("cat data/3.txt");
    printf("\n");
    printf("Data read from offset 10: [%s]\n", buffer);

    close(fd);
    return 0;
}

