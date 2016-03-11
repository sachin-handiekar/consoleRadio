#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#include "icy-string.h"

int extractHeaderFields(ICYHeader *header) {
    char metaint[20];
    getHttpHeader(header->buffer, "icy-name", header->icy_name);
    getHttpHeader(header->buffer, "icy-notice1", header->icy_notice1);
    getHttpHeader(header->buffer, "icy-notice2", header->icy_notice2);
    getHttpHeader(header->buffer, "icy-genre", header->icy_genre);
    getHttpHeader(header->buffer, "icy-pub", header->icy_pub);
    getHttpHeader(header->buffer, "icy-br", header->icy_br);
    getHttpHeader(header->buffer, "icy-metaint", metaint);
    header->metaint = atoi(metaint);
    return 0;
}

int getHttpHeader(char *header, const char *field, char *value) {
    int i;
    char *occurrence = NULL;
    int content_pos = 0;

    occurrence = strstr(header, field);
    content_pos = strlen(field) + 1;
    // TODO : Test NULL value
    for (i = content_pos; occurrence[i] != '\0'; i++) {
        if (isCrPresent(occurrence, i)) {
            // "<field>:" is deleted
            strncpy(value, occurrence + content_pos, i - content_pos);
            value[i - content_pos - 1] = '\0';
            return 0;
        }
    }
    // Value hasn't been found
    value[0] = '\0';
    return 1;
}

int getMetadataField(char *metadata, const char *field, char *value) {
    char *split;
    char *occurrence = NULL;
    split = strtok(metadata, ";");
    while (split != NULL) {
        occurrence = strstr(split, field);
        if (occurrence != NULL) {
            unsigned int content_pos = strlen(field) + 2;
            unsigned int content_size = strlen(split) - content_pos - 1;
            strncpy(value, occurrence + content_pos, content_size);
            value[content_size] = '\0';
            return 0;
        }
        split = strtok(NULL, ";");
    }
    // Value hasn't been found
    value[0] = '\0';
    return 1;
}

int isCrPresent(char *str, int pos) {
    if (str[pos - 1] == '\r' && str[pos] == '\n')
        return TRUE;
    else
        return FALSE;
}

int isEndOfHttpHeader(ICYHeader *header) {
    unsigned int buffer_size = 0;
    buffer_size = header->ptr - header->buffer + 1;

    if (buffer_size < 4)
        return FALSE;

    if (*(header->ptr - 3) == '\r' && *(header->ptr - 2) == '\n'
        && *(header->ptr - 1) == '\r' && *(header->ptr) == '\n')
        return TRUE;
    else
        return FALSE;
}
