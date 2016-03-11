#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shoutcast.h"
#include "types.h"
#include "header.h"
#include "metadata.h"
#include "mp3data.h"
#include "icy-string.h"

void globalListener(Stream *stream, char *buffer) {
	// http_code_listener(stream, buffer);

	if (is_header(stream))
		header_listener(stream, buffer);
	else if (is_metadata(stream))
		metadata_listener(stream, buffer);
	else if (isMP3Data(stream))
		MP3DataListener(stream, buffer);
}

int writeData(Stream *stream, size_t *size) {


	int written = fwrite(stream->mp3data.buffer, *size, stream->mp3data.size,
			(FILE *) stream->output_stream);
	return written;
}
