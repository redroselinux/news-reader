#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lib.h"

int main(int argc, char **argv) {
    if (__builtin_expect(argc == 1, true)) {
        return read_latest();
    }

    if (__builtin_expect(strcmp(argv[1], "help") == 0, true)) {
        puts( // if the first condition isnt true, this ^ is likely
            "news-reader v0.2\n"
            "read the latest redrose linux news\n"
            "\n"
            "usage: news-reader [command] [args]\n"
            "\n"
            "commands:\n"
            "  (no args)      fetch and read latest\n"
            "  read <date>    fetch and read a specific article\n"
            "  help           show this help message\n"
            "\n"
            "example:\n"
            "  news-reader read 2026(9.5)\n"
        );
    } else if (__builtin_expect(strcmp(argv[1], "read") == 0, false)) { // read is the least used cmd
        if (argc < 3) {
            puts("\e[1;91mx\e[0m Missing date argument for read command");
            return 1;
        }
        if (__builtin_expect(!strcmp(argv[2], "latest"), false)) {
            return read_latest();
        }
        return read_article(argv[2]);
    } else {
        puts("\e[1;91mx\e[0m Unknown command");
        return 1;
    }

    return 0;
}
