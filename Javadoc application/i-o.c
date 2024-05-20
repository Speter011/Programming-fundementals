#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i-o.h"

//get input and output files into an array
void io (int argc, char **argv, char **files)
{
	files[0] = argv[2];
	files[1] = argv[4];
}


