
#include "xtlang-parse.h"

#define BIND_VAL_PREFIX "(bind-val "
#define BIND_FUNC_PREFIX "(bind-func "
#define BIND_ALIAS_PREFIX "(bind-alias "
#define BIND_TYPE_PREFIX "(bind-type "
#define DEFINE_PREFIX "(define "

void loadFile(char* filename, char* buffer, int bufferLength)
{
	FILE *fp = fopen(filename, "r");
	if (fp != NULL) 
	{
	    size_t newLen = fread(buffer, sizeof(char), bufferLength, fp);

	    if (newLen == 0) fputs("Error reading file", stderr);
	    else buffer[++newLen] = '\0';

	    fclose(fp);
	}
}


void findByPrefix(char* buffer, char* prefix, struct buffer_set* set)
{
	int i = 0;
	char* previous = buffer;
	while(true)
	{
		char* current = strstr(previous, prefix);
		if(!current) break;
		set->locations[i] = current;

		if(i > 0) current[-1] = '\0';

		if(i > 0) set->lengths[i - 1] = current - previous;
		i++;

		previous = current + 1;
	}

	if(i > 0) set->lengths[i - 1] = strlen(previous);
	set->count = i;
}

 
/**
 * Places contents of file into the data struct.
 * Assumes that the code raw buffer has been allocated.
 */
struct code load(void* file, char* buffer, int bufferLength)
{
	loadFile(file, buffer, bufferLength);

	struct code c;
	
	sscanf(buffer, "%i,%i,%lf\n", &c.startCursor, &c.endCursor, &c.time);
	c.isRegionSelected = (c.startCursor != c.endCursor);
	c.buffer = buffer;
	c.bufferLength = bufferLength;

	//findByPrefix(buffer, BIND_VAL_PREFIX, &c.bind_val_set);
	findByPrefix(buffer, BIND_FUNC_PREFIX, &c.bind_func_set);
	//findByPrefix(buffer, BIND_ALIAS_PREFIX, &c.bind_alias_set);
	//findByPrefix(buffer, BIND_TYPE_PREFIX, &c.bind_type_set);
	//findByPrefix(buffer, DEFINE_PREFIX, &c.define_set);
	
	return c;
}


/**
 * Gets the end of the specified block of code based on if 
 * the code block is in an unstable editing state.
 */
// int editHeuristic(int start, int end, char* buffer, int cursorStart, int cursorEnd)
// {
// 	if(cursorStart > end || cursorEnd < start) return end;
// 	return 0;
// }

// bool gatherBlocks(char* leading, char* buffer, int bufferLength, char** targetStart, int* targetLengths)
// {

// 	// for(int i = 0; i < bufferLength; i++)
// 	// {
// 	// }
// 	return false;
// }

// bool expand(int start, int end, char* buffer, int min, int max)
// {
// 	int newStart = start;
// 	int newEnd = end;

// 	int count = 0;
// 	bool foundStart = false;
// 	for(; newStart >= min; newStart--)
// 	{
// 		if(buffer[newStart] == ')') count++;

// 		if(buffer[newStart] == '(')
// 		{
// 			count--;

// 			if(count == 0)
// 			{
// 				foundStart = true;
// 				break;				
// 			}
// 		}
// 	}

// 	if(!foundStart) return false;

// 	count = 0;
// 	bool foundEnd = false;
// 	for(; newEnd <= max; newEnd++)
// 	{
// 		if(buffer[newEnd] == '(') count++;

// 		if(buffer[newEnd] == ')')
// 		{
// 			count--;

// 			if(count == 0)
// 			{
// 				foundEnd = true;
// 				break;				
// 			}
// 		}
// 	}

// 	if(!foundEnd) return false;

// 	start = newStart;
// 	end = newEnd;

// 	return true;
// }




int main(int argc, char* argv[])
{
	char* buffer = (char*) malloc(sizeof(char) * BUFFER_SIZE);
	struct code c = load("vis.cache", buffer, BUFFER_SIZE);
	//printf("%lf\n", c.time);

	for(int i = 0; i < c.bind_func_set.count; i++)
	{
		//printf("----%.*s\nlength:%d\n", c.bind_func_set.lengths[i], c.bind_func_set.locations[i], c.bind_func_set.lengths[i]);
		printf("------%s\n", c.bind_func_set.locations[i]);
	}


	free(buffer);

	return 0;
}


