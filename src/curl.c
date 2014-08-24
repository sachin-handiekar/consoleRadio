#include <curl/curl.h>
#include <curl/easy.h>
#include <mpg123.h>
#include <ao/ao.h>
#include "types.h"
#include "parsing.h"

#define BITS 8

mpg123_handle *mh = NULL;
ao_device *dev = NULL;
unsigned int metaInt = 0;

size_t parse_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
	unsigned int i;
	char buffer;
	Stream *stream = (Stream *) userdata;

	stream->mp3data.buffer = (char*) malloc(nmemb);
	stream->mp3data.ptr = stream->mp3data.buffer;

	for (i = 0; i < nmemb; i++) {
		buffer = ((char*) ptr)[i];
		global_listener(stream, &buffer);
		stream->bytes_count_total++;
	}

	write_data(stream, &size);
	play_song(stream, size * nmemb);

	free(stream->mp3data.buffer);
	stream->mp3data.size = 0;

	stream->blocks_count++;

	return nmemb;
}

int play_song(Stream *stream, size_t size) {
	int err;
	off_t frame_offset;
	unsigned char *audio;
	size_t done;
	ao_sample_format format;
	int channels, encoding;
	long rate;

	err = mpg123_feed(mh, (const unsigned char*) stream->mp3data.buffer,
			stream->mp3data.size);
	if (stream->status == E_STATUS_MP3DATA)
		do {
			err = mpg123_decode_frame(mh, &frame_offset, &audio, &done);

			switch (err) {
			case MPG123_NEW_FORMAT:
				mpg123_getformat(mh, &rate, &channels, &encoding);
				format.bits = mpg123_encsize(encoding) * BITS;
				format.rate = rate;
				format.channels = channels;
				format.byte_format = AO_FMT_NATIVE;
				format.matrix = 0;
				dev = ao_open_live(ao_default_driver_id(), &format, NULL );
				break;
			case MPG123_OK:

				ao_play(dev, audio, done);
				break;
			case MPG123_NEED_MORE:
				break;
			default:
				break;
			}
		} while (done > 0);

	return err;
}

int read_stream(Stream *stream) {

	ao_initialize();

	mpg123_init();
	mh = mpg123_new(NULL, NULL );
	mpg123_open_feed(mh);

	CURL *curl;
	CURLcode curl_res;
	struct curl_slist *headers = NULL;
	int ret = 0;

	if (stream->url == NULL ) {
		ret = -1;
		goto early_err;
	}

	if ((curl = curl_easy_init()) == NULL ) {
		ret = -1;
		goto early_err;
	}

	headers = curl_slist_append(headers, "Icy-MetaData:1");

	curl_easy_setopt(curl, CURLOPT_URL, stream->url);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);

	// Proxy Server
	// curl_easy_setopt(curl, CURLOPT_PROXY, "proxy.logica.com:80");

	if ((curl_res = curl_easy_perform(curl)) != 0) {
		printf("ERROR : %s\n", curl_easy_strerror(curl_res));
		ret = -1;
		goto err;
	}
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();

	ao_close(dev);
	ao_shutdown();

	err: curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	early_err: return ret;
}
