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
			"Usage: scsv [OPTIONS] [path]\n"
			"\n"
			"Arguments:\n"
			"    path: the path to the CSV file that is to be displayed\n"
			"\n"
			"Options:\n"
			"    -s: shows a non-interactive version of the CSV file\n";
		
		printf("%s", usage);
		
		return 0;
	}

	if (argc == 2)
	{
		if (system("which less > /dev/null 2>&1"))
		{
			fprintf(stderr, "The command less was not found. You should install less to use scsv.\n");
		}
		
		char *path = argv[1];

		// create a unique temp file
		char *dup = strdup(path);
		char temp[FILENAME_MAX] = TEMP_BASE;
		replace_char(dup, '/', '-');
		strcat(temp, dup);
		
		// remove the file just in case it already exists
		remove(temp);

		parse_csv(path, temp);

		// call the less command on the temp file
		char *cmd = "less";
		char *argv[4];
		argv[0] = "less";
		argv[1] = "-S";
		argv[2] = temp;
		argv[3] = NULL;
		execvp(cmd, argv);
		return 0;
	}
	
	if (argc == 3)
	{
		if (system("which cat > /dev/null 2>&1"))
		{
			fprintf(stderr, "The command cat was not found. You should install cat to use scsv.\n");
		}
		
		char *flag = argv[1];
		char *path = argv[2];

		// create a unique temp file
		char *dup = strdup(path);
		char temp[FILENAME_MAX] = TEMP_BASE;
		replace_char(dup, '/', '-');
		strcat(temp, dup);

		// remove the file just in case it already exists
		remove(temp);
		
		// display in simplified form
		if (strcmp(flag, "-s") == 0)
		{
			parse_csv(path, temp);

			// call the cat command on the temp file
			char *cmd = "cat";
			char *argv[3];
			argv[0] = "cat";
			argv[1] = temp;
			argv[2] = NULL;
			execvp(cmd, argv);
			return 0;
		}
		
		return 0;
	}
}
