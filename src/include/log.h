/*
 * log.h
 *
 *  Created on: Aug 25, 2012
 *      Author: SachinHandiekar
 */

#ifndef LOG_H_
#define LOG_H_


int log_open_files(void);
int log_close_files(void);
void slog(char *line);
void slog_prog(char *line);


#endif /* LOG_H_ */
