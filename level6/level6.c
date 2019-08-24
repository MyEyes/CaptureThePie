#include <stdio.h>
#include <stdlib.h>
#include "flag.h"

char name[0x80];

void set_name()
{
	printf("Hey, by the way: What's your name?\n");
	fgets(name, 0x80, stdin);
	printf("Nice to meet you ");
	printf(name);
	printf("\n");
}

void guess()
{
	char input[0x80];
	long int number = random();
	long int guessNum = 0;
	printf("If you guess my number correctly I'll give you the flag\n");
	gets(input);
	guessNum = atoi(input);
	if(guessNum==number)
	{
		//lol, as if I'd give you the flag!
		//printf(FLAG)
	}
	else
	{
		printf("Wrong!");
	}
}

int main(int argc, char **argv)
{
	set_name();
	guess();
}
