#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "stream.h"
#include "files.h"
#include "pls.h"
#include "curl.h"

int loadStream(Stream *stream, const char *url) {
	ICYHeader *header = &stream->header;
	MetaData *metadata = &stream->metadata;
	Mp3Data *mp3data = &stream->mp3data;

	// Setting header
	header->icy_name[0] = '\0';
	header->icy_notice1[0] = '\0';
	header->icy_notice2[0] = '\0';
	header->icy_genre[0] = '\0';
	header->icy_pub[0] = '\0';
	header->icy_br[0] = '\0';
	header->is_set = 0;
	header->buffer = malloc(4000 * sizeof(char));
	header->ptr = header->buffer;
	header->metaint = 0;

	metadata->ptr = NULL;
	metadata->size = 0;

	mp3data->ptr = NULL;

	// Setting Stream information
	stream->bytes_count = 0;
	stream->bytes_count_total = 0;
	stream->blocks_count = 0;
	stream->metadata_count = 0;
	stream->stream_title[0] = '\0';

	stream->status = E_STATUS_HEADER;

	stream->output_stream = fopen("radio0.mp3", "w");
	if (strcpy(stream->url, url) != NULL )
		return 0;
	else
		return 1;
}

int load_stream_from_playlist(char *filename) {
	Stream stream;
	PlsFile pls;
	int ret = 0;

	if (filename == NULL ) {
		ret = -1;
		goto early_err;
	}

	if (!isPlsExtension(filename)) {
		ret = -1;
		goto early_err;
	}

	if ((ret = pls_load_file(filename, &pls)) < 0) {
		printf("Error : Couldn't load pls file\n");
		goto early_err;
	}

	if ((ret = loadStream(&stream, pls.entries->file)) < 0) {
		printf("Error : Couldn't load Shoutcast stream\n");
		goto err;
	}

	if ((ret = read_stream(&stream)) < 0) {
		printf("Error : Couldn't read Shoutcast stream\n");
		goto err;
	}

	err: free(pls.entries);
	early_err: return ret;

}
