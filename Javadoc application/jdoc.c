#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i-o.h"

int main (int argc, char **argv)
{
	char **files;
	files[0] = argv[2];
	files[1] = argv[4];
	io(argc, argv, files);
	FILE *input = fopen(files[0], "r");
	FILE *output = fopen(files[1], "w");
	char line [100];
	int count = 0;
	int lineCount = 0;
	int blankCount = 0;
	int nonBlankCount = 0;
	int commentCount = 0;
	//
	int commentFlag = 0;
	
	//iterate through all the lines, and add one to count on each to get the number of lines
	while (fgets(line, 100, input) != NULL)
	{
			lineCount++;
			
			//iterate through the current line's characters and count the spaces, newlines and tabs, if these add up to the number of characters in the line(length),
			//then the line is blank
			int length = strlen(line);
			for(int i = 0; i < length; i++)
			{
				if(line[i] == ' ')
				{
					count++;
				}
				else if(line[i] == '\t')
				{
					count++;
				}
				else if(line[i] == '\n')
				{
					count++;
				}
				
				
			}
			if(count == length)
			{
				blankCount++;
			}
			
			//check for the Javadoc comment starter characters to count the number of comments
			if(strstr(line, "/**") !=NULL)
			{
				commentFlag = 1;
				commentCount++;
			}
			
			//check for { 
			if(commentFlag == 1)
			{
				
				if(strstr(line, "{") != NULL)
				{	
					fprintf(output,"%s\n",line);
					commentFlag = 0;
					
				}
				else
				{
					fprintf(output,"%s",line);
				}
			}
			
			
			//print out the author, paramaters, and returns
			if(strstr(line, "@author") !=NULL)
			{
				printf("Author: %s", strchr(strstr(line,"@author"),' '));
			}
			if(strstr(line, "@param") !=NULL)
			{
				printf("Parameter: %s", strchr(strstr(line,"@param"),' '));
			}
			if(strstr(line, "@return") !=NULL)
			{
				printf("Returns: %s", strchr(strstr(line,"@return"),' '));
			}
			if(strstr(line, "*/"))
			{
				printf("\n");
			}
			
			count = 0;
	}	
	nonBlankCount = lineCount - blankCount;
	
	//print
	printf("Total number of lines: %d\n", lineCount);
	printf("Number of nonblank-lines: %d\n", nonBlankCount);
	printf("Number of Javadoc comments: %d\n", commentCount);
	
	
	
	fclose(input);
	fclose(output);
	return(0);
}	