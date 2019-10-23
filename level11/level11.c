#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_UCHAR 1
#define TYPE_USHORT 2
#define TYPE_UINT 3

#define MAX_ARRAYS 0x20

typedef struct {
	char name[0x10];
	unsigned char type;
	size_t size;
	void* buffer;
} generic_array_t;

generic_array_t *arrays[MAX_ARRAYS];
unsigned int curArrayIndex = 0;

unsigned int get_array_value(generic_array_t *arr, unsigned int idx);
void set_array_value(generic_array_t *arr, unsigned int idx, unsigned int value);

void* alloc_array(char type, size_t size)
{
	size_t tSize = 1;
	switch(type){
		case TYPE_UCHAR: tSize = 1; break;
		case TYPE_USHORT: tSize = 2; break;
		case TYPE_UINT: tSize = 4; break;
	}

	void* buffer = malloc(tSize*size);
	if (buffer == NULL){
		printf("Couldn't allocate buffer\n");
		return NULL;
	}
	generic_array_t *array = malloc(sizeof(generic_array_t));
	if(array == NULL){
		free(buffer);
		return NULL;
	}
	array->type = type;
	array->size = size;
	array->buffer = buffer;
	printf("Created array with %d entries\n", array->size);
	return array;
}

generic_array_t* find_array(const char *name)
{
	int i;
	for(i=0; i<curArrayIndex; i++)
	{
		if(!arrays[i])
			continue;
		if(!strcmp(arrays[i]->name, name))
			return arrays[i];
	}
	return NULL;
}


unsigned int get_named_array_value(const char *name, unsigned int idx)
{
	generic_array_t *arr = find_array(name);
	if(!arr)
	{
		printf("Couldn't find array %s\n", name);
		return 0;
	}
	return get_array_value(arr, idx);
}

unsigned int get_array_value(generic_array_t *arr, unsigned int idx)
{
	if(!arr)
		return -1;
	
	if(arr->size<=idx)
		return -1;

	if(arr->type == TYPE_UCHAR)
	{
		unsigned char *val = (unsigned char*) arr->buffer;
		return (unsigned int)val[idx];
	}
	else if(arr->type == TYPE_USHORT)
	{
		unsigned short *val = (unsigned short*) arr->buffer;
		return (unsigned int)val[idx];
	}
	else if(arr->type == TYPE_UINT)
	{
		unsigned int *val = (unsigned int*) arr->buffer;
		return *val;
	}
	return 0;
}

void set_named_array_value(const char* name, unsigned int idx, unsigned int value)
{
	generic_array_t *arr = find_array(name);
	if(!arr)
		return;
	set_array_value(arr, idx, value);
}

void set_array_value(generic_array_t *arr, unsigned int idx, unsigned int value)
{
	if(!arr)
		return;
	
	if(arr->size<=idx)
		return;

	if(arr->type == TYPE_UCHAR)
	{
		unsigned char *val = (unsigned char*) arr->buffer;
		val[idx] = (unsigned char)value;
	}
	else if(arr->type == TYPE_USHORT)
	{
		unsigned short *val = (unsigned short*) arr->buffer;
		val[idx] = (unsigned short)value;
	}
	else if(arr->type == TYPE_UINT)
	{
		unsigned int *val = (unsigned int*) arr->buffer;
		*val = value;
	}
}

unsigned int parse_index(char* input)
{
	char *lBrPos = strstr(input, "[");
	char * rBrPos = strstr(input, "]");
	if(lBrPos>input && rBrPos>lBrPos)
	{
		unsigned int val = atoi(lBrPos+1);
		return val;
	}
	return -1;
}

unsigned int resolve_value(char* input)
{
	int index = parse_index(input);
	if(index==(unsigned int)-1)
		return atoi(input);
	char* lBrPos = strstr(input, "[");
	*lBrPos = 0;
	unsigned int value = get_named_array_value(input, index);
	*lBrPos = '[';
	return value;
}

generic_array_t* create_array(char* type_ptr)
{
	int index = parse_index(type_ptr);
	if(index==(unsigned int)-1)
		return NULL;
	if(strstr(type_ptr, "ubyte") || strstr(type_ptr, "uchar"))
		return alloc_array(TYPE_UCHAR, index);
	else if(strstr(type_ptr, "ushort"))
		return alloc_array(TYPE_USHORT, index);
	else if(strstr(type_ptr, "uint"))
		return alloc_array(TYPE_UINT, index);
	return NULL;
}

void parse_assignment(char* lhs, char* rhs)
{
	int lIndex = parse_index(lhs);
	char* newPtr = strstr(rhs, "new ");
	if(newPtr>=rhs)
	{
		if(lIndex != (unsigned int)-1)
			return;
		if(strlen(lhs)>0xF)
			return;
		if(curArrayIndex>=MAX_ARRAYS)
			return;
		generic_array_t* newArray = create_array(newPtr+4);
		if(!newArray)
			return;	
		strcpy(newArray->name, lhs);
		arrays[curArrayIndex++] = newArray;
		return;
	}
	else
	{
		unsigned int val = resolve_value(rhs);
		char* lBr = strstr(lhs, "[");
		*lBr-- = 0;
		while(*lBr==' ')
			*lBr-- = 0;
		generic_array_t* target = find_array(lhs);
		if(!target)
		{
			printf("Couldn't find array %s\n", lhs);
			return;
		}
		set_array_value(target, lIndex, val);
		printf("Assigned %s[%d]=%d\n", lhs, lIndex, val);
	}
}

void parse_line(char *line)
{
	char *eqPos = strstr(line, "=");
	if(eqPos>=line)
	{
		*eqPos = 0;
		parse_assignment(line, eqPos+1);
	}
	else 
	{
		printf("Value: %d\n", resolve_value(line));
	}
}

int main(int argc, char **argv)
{
	char buffer[0x80];
	memset(arrays, 0, sizeof(generic_array_t*)*MAX_ARRAYS);
	memset(buffer, 0, 0x80);
	do
	{
		fgets(buffer, 0x80, stdin);
		buffer[strlen(buffer)-1] = 0;
		parse_line(buffer);
	}
	while (strcmp("exit", buffer));
}
