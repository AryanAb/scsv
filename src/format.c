#include "format.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int store_line(char **csv_row, char *temp, size_t row_len, size_t line_num)
{
	FILE *tmp = fopen(temp, "a");
	if (tmp == NULL)
	{ /* error handling */}

	// draw the top border
	if (line_num == 1)
	{
		for (size_t i = 0; i < row_len * (MAX_STR_LENGTH + 3); ++i)
			fputs("+", tmp);
		fputs("+\r\n", tmp);
	}
	for (size_t i = 0; i < row_len; ++i)
	{
		if (i == 0)
			fputs("+", tmp);
		else
			fputs("|", tmp);

		int lpadding = calc_lpadding(csv_row[i]);
		int rpadding = MAX_STR_LENGTH + 2 - strlen(csv_row[i]) - lpadding;
		for (size_t k = 0; k < lpadding; ++k) fputs(" ", tmp);
		fprintf(tmp, "%s", csv_row[i]);
		for (size_t k = 0; k < rpadding; ++k) fputs(" ", tmp);
	}
	fputs("+\r\n", tmp);
	fputs("+", tmp);
	for (size_t i = 0; i < row_len * (MAX_STR_LENGTH + 3) - 1; ++i)
	{
		fputs("-", tmp);
	}
	fputs("+\r\n", tmp);

	fclose(tmp);
	return 0;
}

static inline int calc_lpadding(const char *str)
{
	return (MAX_STR_LENGTH + 2 - strlen(str)) / 2;
}
