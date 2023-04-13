#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int fd;
    char * msg = "Hello world!\n";
    char c;

    if (mkfifo("mon_tube", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    fd = open("mon_tube", O_WRONLY);
    write(fd, msg, strlen(msg));
    close(fd);

    fd = open("mon_tube", O_RDONLY);
    while (read(fd, &c, 1) > 0) {
        putchar(c);
    }
    close(fd);

    return EXIT_SUCCESS;
}
