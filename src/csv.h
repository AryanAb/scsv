#ifndef _CSV_H
#define _CSV_H

#include <stdlib.h>

struct CSV
{
	char ***table;
	size_t max_rows;
    size_t max_cols;
	size_t num_rows;
	size_t num_cols;
};

int create_CSV(struct CSV *csv, size_t max_rows, size_t max_cols);
int destroy_CSV(struct CSV *csv);

#endif
