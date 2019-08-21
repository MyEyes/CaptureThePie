#include <stdio.h>
#include <strings.h>
#include "flag.h"

int main(int argc, char **argv)
{
	//Using a struct to force the correct stack layout
	struct {
		char buffer[0x80];
		char secret[0x10];
	} local_vars;
	//Initializing the secret with something random
	int i;
	for(i=0; i<0x10; i++)
	{
		local_vars.secret[i] = (char)(random()%94+33);
	}
	printf("Try to guess my secret:\n");
	gets(local_vars.buffer);
	if(!strcmp(local_vars.buffer,local_vars.secret))
	{
		printf("Congratulations, here's your flag %s\n", FLAG);
	}
	else
	{
		printf("Failed!\n");
	}
}
