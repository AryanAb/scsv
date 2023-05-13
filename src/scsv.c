#include "parse.h"
#include "utility.h"
#include "display.h"
#include "csv.h"

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		const char* usage =
			"Command line tool to display CSV files\n"
			"\n"
			"Usage: scsv [path] [OPTIONS]\n"
			"\n"
			"Arguments:\n"
			"    path: the path to the CSV file that is to be displayed\n"
			"\n"
			"Options:\n"
			"    -s: shows a simplified and non-interactive version of the CSV file\n";
		
		printf("%s", usage);
		
		return 0;
	}

	initscr();
	if (argc == 2)
	{
		endwin();
		return 0;
	}
	
	if (argc == 3)
	{
		char *path = argv[1];
		char *flag = argv[2];

		// display in simplified form
		if (strcmp(flag, "-s") == 0)
		{
			int res, max_x, max_y;
			getmaxyx(stdscr, max_y, max_x);
			
			// calculate maximum number of displayable rows and columns
			int max_cols = min(MAX_COLS, (max_x - 1) / (MAX_STR_LENGTH + 3));
			int max_rows = min(MAX_ROWS, (max_y - 1) / 2);

			struct CSV csv;
			res = create_CSV(&csv, max_rows, max_cols);
			res = parse_csv(&csv, path, max_rows, max_cols);
			if (res == -1)
			{
				printf("Inconsistent number of fields in rows\r\n");
				endwin();
				return 1;
			}
			
			display(&csv);
			
			destroy_CSV(&csv);
			endwin();
		}
		
		return 0;
	}
}
