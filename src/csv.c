#include "csv.h"

#include <stdio.h>

int create_CSV(struct CSV *csv, size_t max_rows, size_t max_cols)
{
	// create a 2d array of strings to represent the csv file
	csv->table = malloc(sizeof(char**) * max_rows);
	for (int i = 0; i < max_rows; ++i)
	{
		csv->table[i] = malloc(sizeof(char*) * max_cols);
	}
	for (int i = 0; i < max_rows; ++i)
		for (int j = 0; j < max_cols; ++j)
			csv->table[i][j] = NULL;
	
	csv->max_rows = max_rows;
	csv->max_cols = max_cols;

	csv->num_rows = 0;
	csv->num_cols = 0;

	return 0;
}

int destroy_CSV(struct CSV *csv)
{
	for (int i = 0; i < csv->max_rows; ++i)
	{
		for (int j = 0; j < csv->max_cols; ++j)
		{
			free(csv->table[i][j]);
		}
		free(csv->table[i]);
	}
	free(csv->table);

	return 0;
}
