
#ifndef CALKUC_STRINGBUFFER_H
#define CALKUC_STRINGBUFFER_H

typedef struct {
    int cap;
    int len;
    char* str;
} StringBuffer;

StringBuffer* strbuf_new();
int strbuf_append_char(StringBuffer*, char);
int strbuf_parse_number(StringBuffer*, double*);
void strbuf_empty(StringBuffer*);
void strbuf_free(StringBuffer*);

#endif