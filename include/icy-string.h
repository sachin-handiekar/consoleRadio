#ifndef ICY_STRING_H_
#define ICY_STRING_H_

#include "types.h"

int extractHeaderFields(ICYHeader *header);

int getHttpHeader(char *header, const char *field, char *value);

int getMetadataField(char *metadata, const char *field, char *value);

int isCrPresent(char *str, int pos);

int isEndOfHttpHeader(ICYHeader *header);

#endif /* ICY_STRING_H_ */
