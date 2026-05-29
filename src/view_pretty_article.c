#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lib.h"

void view_pretty_article(char *restrict text) {
    char* text_copy = strdup(text);
    char *line;
    char* title = NULL;
    char* action_needed = NULL;
    char body[8128] = {0};
    size_t body_len = 0;
    bool in_body = false;

    line = strtok(text_copy, "\n");
    while (line != NULL) {
        if (startswith(line, "TITLE: ")) {
            title = strdup(line + 7);
        } else if (startswith(line, "ACTION-NEEDED: ")) {
            const char* action_needed_str = line + 15;
            if (strcmp(action_needed_str, "true") == 0) {
                action_needed = strdup("(\e[91maction required\e[0m)");
            } else if (strcmp(action_needed_str, "false") == 0) {
                action_needed = strdup("(\e[92maction not required\e[0m)");
            } else {
                action_needed = strdup("");
            }
        } else if (!strcmp(";", line)) {
            in_body = !in_body;
        } else if (in_body) {
            size_t line_len = strlen(line);
            if (body_len + line_len + 2 < 8128) {
                body_len += snprintf(body + body_len, 8128 - body_len, "%s\n", line);
            }
        }
        line = strtok(NULL, "\n");
    }

    printf("\e[1;92m→\e[0m %s", title ? title : "Unknown title");
    if (action_needed) {
        printf(" %s", action_needed);
    }
    puts("");
    printf("%s", body);

    free(text_copy);
    free(title);
    free(action_needed);
}
