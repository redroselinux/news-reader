#ifndef LIB_H
#define LIB_H

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#define startswith(str, prefix) (strncmp((str), (prefix), strlen(prefix)) == 0)

int read_latest();
int read_article(char* article);
char *fetch(const char *url);
void view_pretty_article(char *filename);

#endif
