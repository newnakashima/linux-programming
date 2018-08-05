#include <stdio.h>
#include <stdlib.h>

static void
do_cat(FILE *f);

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
            perror(argv[i]);
            exit(1);
        }
        do_cat(f);
        fclose(f);
    }
    exit(0);
}

static void
do_cat(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF) {
        if ((char)c == '\t') {
            if (putchar((int)'\\') < 0) exit(1);
            if (putchar((int)'t') < 0) exit(1);
        } else if ((char)c == '\n') {
            if (putchar((int)'$') < 0) exit(1);
            if (putchar(c) < 0) exit(1);
        } else {
            if (putchar(c) < 0) exit(1);
        }
    }
}
