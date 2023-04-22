#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef STR_HEADER
#define STR_HEADER

typedef struct {
    char *string;
    size_t length;
} Str;

typedef struct {
    Str **strs;
    size_t num_strs;
    size_t current_str;
} StrArray;

typedef struct {
    FILE *file;
    size_t fp;
} StrReader;

Str *str_new(char *string);
StrArray *str_array_new();
StrReader *str_reader_new(FILE *file);

StrArray *str_split_by(Str *str, const char delim);

Str *str_new_blank(size_t length);
Str *str_concat(Str *str1, Str *str2);
Str *str_read_line(StrReader *reader);

void str_free(Str *str);
void str_reader_free(StrReader *reader);

void str_realloc(Str *str, size_t new_size);
void str_append(Str *str, const char new_char);

#endif

#ifdef STR_HEADER_IMPLEMENTATION

StrReader *str_reader_new(FILE *file) {
    StrReader *reader = malloc(sizeof(StrReader));
    reader->file = file;
    reader->fp = 0;
    return reader;
}

Str *str_read_line(StrReader *reader) {
    Str *str = str_new_blank(0);

    char c;
    while ((c = fgetc(reader->file)) != '\n') {
        if (feof(reader->file)) {
            break;
        }
        str_append(str, c);
    }
    
    return str;
}

void str_reader_free(StrReader *reader) {
    fclose(reader->file);
    free(reader);
}

Str *str_copy(Str *str) {
    return str_new(str->string);
}

StrArray *str_array_new() {
    StrArray *array = malloc(sizeof(StrArray));
    array->num_strs = 0;
    array->current_str = 0;
    array->strs = (Str **)malloc(sizeof(Str*) * array->num_strs);
    return array;
}

void str_array_realloc(StrArray *array) {
    array->num_strs++;
    array->strs = realloc(array->strs, sizeof(Str*) * array->num_strs);
}

void str_array_add(StrArray *array, Str *str) {
    str_array_realloc(array);
    array->strs[array->num_strs - 1] = str;
}


Str *str_new(char *string) {
    Str *str = malloc(sizeof(Str));
    str->string = malloc(sizeof(char) * strlen(string));
    str->length = strlen(string);
    for (size_t i = 0; i < str->length; i++) {
        str->string[i] = string[i];
    }
    return str;
}

Str *str_new_blank(size_t length) { 
    Str *str = malloc(sizeof(Str));
    str->string = malloc(sizeof(char) * length);
    str->length = length;
    return str;
}

Str *str_concat(Str *str1, Str *str2) {
    size_t new_length = str1->length + str2->length;
    Str *new_str = str_new_blank(new_length);
    for (size_t i = 0; i < str1->length; i++) {
        new_str->string[i] = str1->string[i];
    }
    for (size_t i = str1->length; i < new_length; i++) {
        new_str->string[i] = str2->string[i - str1->length];
    }
    str_free(str1);
    str_free(str2);
    return new_str;
}

bool str_in(Str *str, const char find) {
    for (size_t i = 0; i < str->length; i++) {
        if (str->string[i] == find) {
            return true;
        }
    }
    return false;
}

Str *str_trim_left(Str *str) {
    Str *new = str_new_blank(0);
    bool add = false;
    for (size_t i = 0; i < str->length; i++) {
        if (str->string[i] != ' ') {
            add = true;
        }
        if (add) {
            str_append(new, str->string[i]);
        }
    }
    new->string[new->length] = '\0';
    str_free(str);
    return new;
}

StrArray *str_split_by(Str *str, const char delim) {
    //this function is kinda goofy ngl
    StrArray *array = str_array_new();
    Str *tmp = str_new_blank(0);

    size_t reference_count = 0;
    void **references = malloc(sizeof(void *) * reference_count);
    size_t size = 0;
    for (size_t i = 0; i < str->length; i++) {
        if (str->string[i] != delim) {
            str_append(tmp, str->string[i]);
            size++;
        }
        else {
            tmp->string[size] = '\0';
            str_array_add(array, str_copy(tmp));

            reference_count++;
            references = realloc(references, sizeof(void *) * reference_count);
            references[reference_count - 1] = (void *)tmp;

            tmp = str_new_blank(0);
            size = 0;
        }
    }
    tmp->string[size] = '\0';
    str_array_add(array, str_copy(tmp));

    for (size_t i = 0; i < reference_count; i++) {
        str_free(references[i]);
    }
    str_free(tmp);
    free(references);

    return array;
}
 
void str_realloc(Str *str, size_t new_size) {
    str->length = new_size;
    str->string = realloc(str->string, sizeof(char) * new_size);
}

void str_append(Str *str, const char new_char) {
    str_realloc(str, str->length + 1);
    str->string[str->length-1] = new_char;
}

void str_free(Str *str) {
    free(str->string);
    free(str);
}

void str_array_free(StrArray *array) {
    for (size_t i = 0; i < array->num_strs; i++) {
        str_free(array->strs[i]);
    }
    free(array->strs);
    free(array);
}

#endif
