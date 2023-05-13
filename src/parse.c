#include "parse.h"
#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Parses the csv file and returns the result in the csv table stucture. The result
 * is buffered with the max size of the buffer specified.
 *
 * @param path the path to the csv file.
 * @param max_rows the maximum number of rows to be allocated in the buffer
 * @param max_cols the maximum number of columns to be allocated in the buffer
 *
 * @return a 2d table of strings representing the csv table
*/
int parse_csv(struct CSV *csv, char *path, size_t max_rows, size_t max_cols)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(path, "r");
	if (fp == NULL)
	{ /* error handling */ }

	// iterate the lines of the csv file line by line
	size_t i = 0;
	while ((read = getline(&line, &len, fp)) != -1 && i < csv->max_rows)
	{
		// parse each line of the csv file and add it as a row to the csv table
		size_t row_len = parse_line(csv->table[i], line, max_cols);
		if (csv->num_cols != 0 && csv->num_cols != row_len)
			return -1;
		csv->num_cols = row_len;
		++i;
	}
	csv->num_rows = i;

	free(line);
	fclose(fp);
	return 0;
}


static size_t parse_line(char **csv_table_row, char *line, size_t max_cols)
{
	char *token = strtok_csv(line, ",");

    size_t i = 0;
	while (token)
	{
		char *etoken = ellipsize(token);
		csv_table_row[i] = etoken;
		++i;
		token = strtok_csv(NULL, ",");
		
		if (token && i == max_cols)
		{
			free(csv_table_row[i - 1]);
			csv_table_row[i - 1] = strdup("...");
			break;
		}
	}

	// strip the last value from the \n character
	char *last_field = csv_table_row[i - 1];
	if (last_field[strlen(last_field) - 1] == '\n')
		last_field[strlen(last_field) - 1] = '\0';

	return i;
}


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
