#include "parse.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parses the csv file and returns the result in the csv table stucture. The result
 * is buffered with the max size of the buffer specified.
 *
 * @param path the path to the csv file.
 * @param temp the path to the temporary file created in the /tmp directory
 *
 * @return an integer indicating if the parsing was successful or not
*/
int parse_csv(char *path, char *temp)
{
	int res;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t line_num = 1;

	fp = fopen(path, "r");
	if (fp == NULL)
	{ /* error handling */ }

	// iterate the lines of the csv file line by line
	while ((read = getline(&line, &len, fp)) != -1)
	{
		size_t row_len = num_char(line, ',');
		char **csv_row = malloc(sizeof(char **) * row_len);
		for (size_t i = 0; i < row_len; ++i)
			csv_row[i] = NULL;
		
		// parse each line of the csv file and add it as a row to the csv table
		parse_line(csv_row, line);
		res = store_line(csv_row, temp, row_len, line_num);
		
		for (size_t i = 0; i < row_len; ++i)
			free(csv_row[i]);
		free(csv_row);

		++line_num;
	}

	free(line);
	fclose(fp);
	return res;
}


/**
 * Parses a single line of the csv file and stores the result in an array of strings.
 *
 * @param csv_table_row the 2d array of strings in which the entries are stored
 * @param line the line that is to be parsed
 *
 * @return an integer indicating if the parsing was successful or not
 */
static int parse_line(char **csv_table_row, char *line)
{
	char *token = strtok_csv(line, ",");

    size_t i = 0;
	while (token)
	{		
		char *etoken = ellipsize(token);
		csv_table_row[i] = etoken;
		++i;
		token = strtok_csv(NULL, ",");
	}

	// strip the last value from the \n character
	char *last_field = csv_table_row[i - 1];
	if (last_field[strlen(last_field) - 1] == '\n')
		last_field[strlen(last_field) - 1] = '\0';

	return 0;
}


/**
 * Shortens strings of lengths greater than a certain amount and appends ellipses.
 * That certain amount is defined by the macro MAX_STR_LENGTH.
 *
 * @param str the string to be ellipsized
 *
 * @return a heap allocated string that is either ellipsized or unchanged
 */
static char *ellipsize(char *str)
{
	size_t len = strlen(str);
	if (len > MAX_STR_LENGTH)
	{
		size_t substr_len = MAX_STR_LENGTH - 3;
		char *estr = malloc(sizeof(char) * substr_len);
		memcpy(estr, str, substr_len);
		char *ellipses = "...";
		strcat(estr, ellipses);

		return estr;
	}

	char *estr = malloc(sizeof(char) * len);
	strcpy(estr, str);
	return estr;
}


/**
 * Similar to strtok, but handles empty substrings.
 *
 * @param str the string that is to be tokenized
 * @param delimiter the delimiter used to tokenize str with
 *
 * @return the substring in str before the next occurance of delimiter
 */
static char *strtok_csv(char *str, const char *delimiter)
{
	static char *source = NULL;
	char *p, *res = 0;
	if (str != NULL)
		source = str;
	if (source == NULL)
		return NULL;

	if ((p = strpbrk(source, delimiter)) != NULL)
	{
		*p = 0;
		res = source;
		source = ++p;
	}
	return res;
}


/**
 * Finds the number of occurances of a character in a string.
 *
 * @param str the string to search in
 * @param c the character to search for
 */
static inline size_t num_char(char *str, char c)
{
	size_t res = 0;
	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (str[i] == c)
			++res;
	}
	return res;
}
