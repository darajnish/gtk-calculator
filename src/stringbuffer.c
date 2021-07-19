
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringbuffer.h"

StringBuffer* strbuf_new() {
    StringBuffer *buf;
    buf = (StringBuffer*) malloc(sizeof(StringBuffer));

    if (buf == NULL) {
        return NULL;
    }

    buf->cap = 10;
    buf->len = 0;
    buf->str = (char*) malloc(sizeof(char) * (buf->cap));

    if (buf->str == NULL) {
        return NULL;
    }

    strcpy(buf->str, "");
    return buf;
}

int strbuf_append_char(StringBuffer* buf, char c) {
    if (buf == NULL) {
        return -1;
    }

    if (buf->len >= buf->cap) {
        buf->str = (char*) realloc(buf->str, sizeof(char) * (buf->cap += 10));
    }

    strncat(buf->str, &c, 1);
    buf->len += 1;
    return 0;
}

int strbuf_parse_number(StringBuffer* buf, double *num) {
    if (buf == NULL) {
        return -1;
    }

    if (sscanf(buf->str, "%lf", num) != 1) {
        return 2;
    }
    
    return 0;
}

void strbuf_empty(StringBuffer* buf) {
    if (buf == NULL) {
        return;
    }
    strcpy(buf->str, "");
    buf->len = 0;
}
void strbuf_free(StringBuffer* buf) {
    if (buf == NULL) {
        return;
    }

    free(buf->str);
    free(buf);
}