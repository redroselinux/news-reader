#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "lib.h"

static size_t write_cb(void *restrict src, size_t size, size_t n, void *userp) {
    size_t bytes = size * n;
    char **out = (char **)userp;
    size_t old = *out ? strlen(*out) : 0;
    char *buf = realloc(*out, old + bytes + 1);

    if (__builtin_expect(!buf, false))
        return 0;

    memcpy(buf + old, src, bytes);
    buf[old + bytes] = '\0';
    *out = buf;
    return bytes;
}

/*
 * fetch - blocking HTTP GET for @url
 *
 * Returns a heap-allocated NUL-terminated response body.
 * Caller must free() the result if its not "error".
 * Returns "error" on failure.
 */
char *fetch(const char *url) {
    char *out = NULL;
    CURL *curl = curl_easy_init();
    if (__builtin_expect(!!!curl, false)) return "error";

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (__builtin_expect(res != CURLE_OK, false)) {
        free(out);
        fprintf(stderr, "\e[1;91mx\e[0m Curl error: %d\n", res);
        return "error";
    }
    return out;
}
