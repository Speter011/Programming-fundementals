#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i-o.h"
#include "lines.h"

//counts all the lines in the given file
int line_counter(int argc, char **argv)
{
	char **files = i_o(argc, argv[]);
	FILE *input = fopen(files[0], "r");
	char line [100];
	int lineCount = 0;
	
	//iterate through all the lines, and add one to count on each
	while (fgets(line, 100, input) != NULL)
	{
			lineCount++;
	}	
	printf("There are %d lines in the file\n", lineCount);
	fclose(input);
	return lineCount;
}

//counts all blank lines (which have no characters except for \n, \t, and space) 
int non_blank_counter(int argc, char **argv)
{
	char **files = i_o(argc, argv[]);
	FILE *input = fopen(files[0], "r");
	char line [100];
	int blankCount = 0;
	int nonBlankCount = 0;
	int lineCount = line_counter(argc, argv[]);
	
	//
	while (fgets(line, 100, input) != NULL)
	{
		int length = strlen(line);
		
		/*for(int i = 0, i < length, i++)
		{
			if(line[i] cmp \t \n ' '
			count++
		
		
		}
		*/
	}
	nonBlankCount = lineCount - blankCount;
	
	fclose(input);
	return nonBlankCount;
}

//count the amount of comments in the given file
int comment_counter(int argc, char **argv)
{
	char **files = i_o(argc, argv[]);
	FILE *input = fopen(files[0], "r");
	char line [100];
	int commentCount = 0;
	
	//iterate through the file and check for comment starting characters
	while(fgets(line, 100, input) !=NULL)
	{
		if(strstr(line,"/**") !=NULL)
		{
			commentCount++;
		}
	
	}
	
	fclose(input);
	return commentCount;
}