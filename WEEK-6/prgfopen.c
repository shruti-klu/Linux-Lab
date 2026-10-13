#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    const char *msg = "Hello, file descriptors!\n";
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }
    printf("opened out.txt as fd %d\n", fd);
    if (write(fd, msg, strlen(msg)) < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    fd = open("out.txt", O_RDONLY);
    if (fd < 0) { perror("open"); return 1; }
    char buf[64];
    ssize_t n = read(fd, buf, sizeof(buf)-1);
    if (n < 0) { perror("read"); close(fd); return 1; }
    buf[n] = '\0';
    write(STDOUT_FILENO, buf, n);
    lseek(fd, 7, SEEK_SET);
    n = read(fd, buf, 4);
    buf[n] = '\0';
    printf("after lseek: %s\n", buf);
    close(fd);
    return 0;
}
