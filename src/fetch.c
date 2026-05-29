#include "lib.h"
#include <string.h>

int read_latest() {
    // first fetch latest url, read from there and fetch that
    char *url = fetch(
        "https://github.com/redroselinux/news-reader/raw/refs/heads/master/news/latest"
    );
    if (strcmp("error", url) == 0) {
        puts("\e[1;91mx\e[0m Error during fetch");
        return 1;
    }

    // if there is a newline remove it
    if (url[strlen(url) - 1] == '\n') {
        url[strlen(url) - 1] = '\0';
    }

    // fetch the url we just got
    printf("\e[94m→\e[0m Fetching %s\n", url);
    char *content = fetch(url);
    free(url);
    if (strcmp("error", content) == 0) {
        puts("\e[1;91mx\e[0m Error during fetch");
        return 1;
    }

    view_pretty_article(content);

    free(content);
    return 0;
}

int read_article(char* article) {
    char url[512];
    snprintf(url, 512, "https://raw.githubusercontent.com/redroselinux/news-reader/refs/heads/master/news/%s", article);

    printf("\e[1;94m→\e[0m Fetching %s\n", url);
    char *content = fetch(url);
    if (strcmp("error", content) == 0) {
        puts("\e[1;91mx\e[0m Error during fetch");
        return 1;
    }
    if (!strcmp("404: Not Found", content)) {
        puts("\e[1;91mx\e[0m Article does not exist");
        return 1;
    }

    view_pretty_article(content);

    free(content);
    return 0;
}
