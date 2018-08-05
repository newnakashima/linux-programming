#include <stdio.h>
#include <stdlib.h>

static void
do_cat(FILE *f);

static void
die(const char *s);

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        do_cat(stdin);
        exit(0);
    }

    for (i = 1; i < argc; i++) {
        FILE *f;

        f = fopen(argv[i], "r");
        if (!f) {
            die(argv[i]);
        }
        do_cat(f);
        fclose(f);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
do_cat(FILE *f)
{
    unsigned char buf[BUFFER_SIZE];
    for (;;) {
        size_t n_read = fread(buf, 1, sizeof buf, f);
        if (ferror(f)) die("エラーが起きました");
        size_t n_written = fwrite(buf, 1, n_read, stdout);
        if (n_written < n_read) die("エラーが起きました");
        if (n_read < sizeof buf) break;
    }
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
