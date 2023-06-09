#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdio.h>

#define TEMP_BASE "/tmp/tempscsv"

int store_line(char **csv_row, char *temp, size_t row_len, size_t line_num);
int replace_char(char *str, char c, char r);

static int calc_lpadding(const char *str);

#endif
