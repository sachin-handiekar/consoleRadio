#ifndef SHOUTCAST_H_
#define SHOUTCAST_H_

#include "types.h"

int loadStream(Stream *stream, const char *url);

void globalListener(Stream *stream, char *buffer);

int writeData(Stream *stream, size_t *size);

#endif /* SHOUTCAST_H_ */
