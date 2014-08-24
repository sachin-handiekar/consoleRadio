/*
 * mp3data.h
 *
 *  Created on: Aug 25, 2012
 *      Author: SachinHandiekar
 */

#ifndef MP3DATA_H_
#define MP3DATA_H_


#include "types.h"

int is_mp3data(Stream *stream);
int mp3data_listener(Stream *stream, char *buffer);

#endif /* MP3DATA_H_ */
