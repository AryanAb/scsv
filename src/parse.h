#ifndef _PARSE_H
#define _PARSE_H

#include "csv.h"

// define the constrains on the display dimenssions
#define MAX_STR_LENGTH 12
#define MAX_ROWS 100
#define MAX_COLS 100

int parse_csv(struct CSV *csv, char *path, size_t max_rows, size_t max_cols);

static char *ellipsize(char *str);
static size_t parse_line(char **csv_table_row, char *line, size_t max_cols);
static char *strtok_csv(char *str, char const *delimiter);

#endif
