#include "display.h"
#include "csv.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(struct CSV *csv)
{
	for (size_t i = 0; i < csv->num_cols * (MAX_STR_LENGTH + 3); ++i)
		printf("+");
	printf("+\r\n");

	for (size_t i = 0; i < csv->num_rows; ++i)
	{
		for (size_t j = 0; j < csv->num_cols; ++j)
		{
			if (j == 0)
				printf("+");
			else
				printf("|");

			int lpadding = calc_lpadding(csv->table[i][j]);
			int rpadding = MAX_STR_LENGTH + 2 - strlen(csv->table[i][j]) - lpadding;
			for (size_t k = 0; k < lpadding; ++k) printf(" ");
			printf("%s", csv->table[i][j]);
			for (size_t k = 0; k < rpadding; ++k) printf(" ");

			if (strcmp("...", csv->table[i][j]) != 0 && j == csv->max_cols)
				printf("+");
			else if (j == csv->num_cols - 1)
				printf("+");
		}
		printf("\r\n");
		printf("+");
		for (size_t j = 0; j < csv->num_cols * (MAX_STR_LENGTH + 3) - 1; ++j)
		{
			if (i == csv->num_rows - 1)
				printf("+");
			else
				printf("-");
		}
		printf("+\r\n");
		
	}
}

static inline int calc_lpadding(const char *str)
{
	return (MAX_STR_LENGTH + 2 - strlen(str)) / 2;
}
