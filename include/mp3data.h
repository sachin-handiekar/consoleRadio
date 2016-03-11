#ifndef MP3DATA_H_
#define MP3DATA_H_

#include "types.h"

int isMP3Data(Stream *stream);

int MP3DataListener(Stream *stream, char *buffer);

#endif /* MP3DATA_H_ */
