#include "format.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Formats and stores a line of the csv file in the temporary file
 *
 * @param csv_row array of strings that contains that line's entries
 * @param temp the path to the temporary file
 * @param row_len the number of entries on the current line
 * @param line_num the line number of the current line
 *
 * @return an integer indicating if the function was successful or not
 */
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


/**
 * Replace all occurances of a chacater in string.
 *
 * @param str the string to iterate over
 * @param c the character that is removed
 * @param r the character that is inserted instead
 *
 * @return an integer indicating if it was successful or not
 */
int replace_char(char *str, char c, char r)
{
	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (str[i] == c)
		{
			str[i] = r;
		}
	}

	return 0;
}


/**
 * Calculates the left padding needed for a string.
 *
 * @param str the string to calculate the padding for
 *
 * @return the amount of padding required
 */
static inline int calc_lpadding(const char *str)
{
	return (MAX_STR_LENGTH + 2 - strlen(str)) / 2;
}
