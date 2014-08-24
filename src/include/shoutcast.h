/*
 * shoutcast.h
 *
 *  Created on: Aug 25, 2012
 *      Author: SachinHandiekar
 */

#ifndef SHOUTCAST_H_
#define SHOUTCAST_H_


#include "types.h"

int load_stream(Stream *stream, const char *url);
void global_listener(Stream *stream, char *buffer);
int write_data(Stream *stream, size_t *size);

#endif /* SHOUTCAST_H_ */
