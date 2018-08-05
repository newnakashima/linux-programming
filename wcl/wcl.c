#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void wcl_input();
static void wcl(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;
    if (argc < 2) {
        wcl_input();
        exit(0);
    }
    for (i = 1; i < argc; i++) {
        wcl(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048
#define CHAR_SIZE 16

static void
wcl_input()
{
    unsigned char buf[BUFFER_SIZE];
    int n;
    int count = 0;
    int i;
    char count_char[CHAR_SIZE];

    for (;;) {
        n = read(STDIN_FILENO, buf, sizeof buf);
        if (n < 0) die("no input:");
        if (n == 0) break;
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n') count++;
        }
    }
    sprintf(count_char, "%d\n", count);
    if (write(STDOUT_FILENO, count_char, CHAR_SIZE) < 0) die("no input");
}

static void
wcl(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;
    int count = 0;
    int i;
    char count_char[CHAR_SIZE];

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);

    for (;;) {
        n = read(fd, buf, sizeof buf);
        if (n < 0) die(path);
        if (n == 0) break;
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n') count++;
        }
    }
    sprintf(count_char, "%d\n", count);
    if (write(STDOUT_FILENO, count_char, CHAR_SIZE) < 0) die(path);
    if (close(fd) < 0) die(path);
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
