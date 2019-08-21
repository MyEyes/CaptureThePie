#include <stdio.h>
#include "flag.h"

void win()
{
	printf("Wait, what? How?\n%s\n", FLAG);
}

void test()
{
	char buffer[0x80];
	printf("This time, there really is no way to get to the flag.\nDo you finally give up?\n");
	gets(buffer);
	if(strcmp(buffer,"Yes")){
		printf("That wasn't a \"Yes\"\nYou better give up now\n");
	}
	else
	{
		printf("Damn right\n");
	}
}

int main(int argc, char **argv)
{
	test();
}
