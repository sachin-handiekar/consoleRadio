/*
 * icy-string.h
 *
 *  Created on: Aug 25, 2012
 *      Author: SachinHandiekar
 */

#ifndef ICY_STRING_H_
#define ICY_STRING_H_


#include "types.h"

int extract_header_fields(ICYHeader *header);
int get_http_header_field(char *header, const char* field, char* value);
int get_metadata_field(char *metadata, const char* field, char* value);
int is_cr_present(char *str, int pos);
int is_end_of_http_header(ICYHeader *header);

#endif /* ICY_STRING_H_ */
