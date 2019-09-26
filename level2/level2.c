#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flag.h"

char check[0x20];

int main(int argc, char **argv)
{
	struct{
		char buffer[0x80];
		char secret[0x20];
	} local;
	char tmpBuffer[0x100];
	memset(local.buffer, 0, sizeof(local.buffer));
	strcpy(local.secret, FLAG);
	strcpy(check, FLAG);

	printf("Ha!\nI learned my lesson.\nThis time there's a redundancy check and the secret is the flag!\nSo if you overwrite it, you get nothing!\nWhat's your guess?\n");

	gets(tmpBuffer);
	strncpy(local.buffer, tmpBuffer, strlen(tmpBuffer));

	if(strcmp(local.secret,check)){
		printf("You think you can overwrite my secret? No way!\n");
	}
	else if(strcmp(local.secret,local.buffer))
	{
		printf("Wrong!\n");
	}
	else
	{
		printf("That's right!\n");
	}
}
