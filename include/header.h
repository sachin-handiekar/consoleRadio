#ifndef HEADER_H_
#define HEADER_H_

#include "types.h"

int print_header(ICYHeader *header);

int header_listener(Stream *stream, char *buffer);

int is_header(Stream *stream);

#endif /* HEADER_H_ */
