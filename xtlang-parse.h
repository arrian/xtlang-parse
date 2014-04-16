
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

#define SIZE 10
#define BUFFER_SIZE 1000000

// struct buffer_set
// {
// 	char* locations[SIZE];
// 	int lengths[SIZE];
// 	int count;
// };

//Grab parsed code from a text file
struct code 
{
	char* buffer;
	int bufferLength;

	int startCursor;
	int endCursor;

	double time;

	char* funcText[SIZE];
	int funcLengths[SIZE];
	int funcCount;
};

struct code load(void* file, char* buffer, int bufferLength);