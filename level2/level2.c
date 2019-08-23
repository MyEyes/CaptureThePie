#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flag.h"

int main(int argc, char **argv)
{
	struct{
		char buffer[0x80];
		char secret[0x20];
		char check[0x20];
	} local;
	char tmpBuffer[0x100];

	strcpy(local.secret, FLAG);
	strcpy(local.check, FLAG);

	printf("Ha!\nI learned my lesson.\nThis time there's a redundancy check and the secret is the flag!\nSo if you overwrite it, you get nothing!\nWhat's your guess?\n");

	gets(tmpBuffer);
	strncpy(local.buffer, tmpBuffer, strlen(tmpBuffer));
	if(strlen(tmpBuffer)<0x80){
		local.buffer[strlen(tmpBuffer)+1]=0;
	}

	if(strcmp(local.secret,local.check)){
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
