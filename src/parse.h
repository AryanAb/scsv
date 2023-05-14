#ifndef _PARSE_H
#define _PARSE_H

#include <stdlib.h>

// define the constrains on the display dimenssions
#define MAX_STR_LENGTH 12
#define MAX_ROWS 100
#define MAX_COLS 100

int parse_csv(char *path, char *temp);

static char *ellipsize(char *str);
static int parse_line(char **csv_row, char *line);
static char *strtok_csv(char *str, char const *delimiter);
static inline size_t num_char(char *str, char c);

#endif
