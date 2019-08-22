#include <stdio.h>
#include "flag.h"

char buffer[0x80];

void test()
{
	char buffer2[0x80];
	printf("I'll just echo back whatever you send me, twice\n");
	gets(buffer);
	printf(buffer);
	gets(buffer2);
	printf(buffer2);
}

int main(int argc, char **argv)
{
	printf("Alright, maybe I was too confident last time.\nSo this time I'm not going to tell you where things are.\n");
	test();
}
