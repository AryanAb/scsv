#include "parse.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
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

	if (argc == 2)
	{
		char *path = argv[1];
		remove(TEMP_BASE);
		
		parse_csv(path, TEMP_BASE);

		char *cmd = "less";
		char *argv[4];
		argv[0] = "less";
		argv[1] = "-S";
		argv[2] = TEMP_BASE;
		argv[3] = NULL;
		execvp(cmd, argv);
		return 0;
	}
	
	if (argc == 3)
	{
		char *flag = argv[1];
		char *path = argv[2];

		char temp[FILENAME_MAX] = TEMP_BASE;
		strcat(temp, path);
		remove(temp);
		
		// display in simplified form
		if (strcmp(flag, "-s") == 0)
		{
			parse_csv(path, TEMP_BASE);
			
			char *cmd = "cat";
			char *argv[3];
			argv[0] = "cat";
			argv[1] = TEMP_BASE;
			argv[2] = NULL;
			execvp(cmd, argv);
			return 0;
		}
		
		return 0;
	}
}
