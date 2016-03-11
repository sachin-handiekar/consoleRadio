#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <unistd.h> // linux
#include <regex.h>

#include "types.h"
#include "parsing.h"
#include "shoutcast.h"
#include "curl.h"
#include "log.h"

int load_stream_from_playlist(char *filename);

int main1() {
    int ret = 0;
    log_open_files();

    Stream *stream;

    // 181.FM - Power 181
    //   char *streamUrl = "http://7639.live.streamtheworld.com:80/977_HITSAAC_SC";

    // RadioTeentaal
    char *streamUrl = "http://www.radioteentaal.com:8000";


    ret = loadStream(&stream, streamUrl);


    if (ret) {
        printf("Error : Couldn't load Shoutcast stream\n");
        return -1;
    }

    ret = read_stream(&stream);
    if (ret) {
        printf("Error : Couldn't read Shoutcast stream\n");
        return -1;
    }

    err:
    log_close_files();
    return ret;
}
