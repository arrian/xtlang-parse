
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

#define SIZE 10
#define BUFFER_SIZE 1000000

struct buffer_set
{
	char* locations[SIZE];
	int lengths[SIZE];
	int count;
};

//Grab parsed code from a text file
struct code 
{
	char* buffer;
	int bufferLength;

	int startCursor;
	int endCursor;
	bool isRegionSelected;

	double time;

	struct buffer_set bind_val_set;
	struct buffer_set bind_func_set;
	struct buffer_set bind_alias_set;
	struct buffer_set bind_type_set;
	struct buffer_set define_set;
};

struct code load(void* file, char* buffer, int bufferLength);