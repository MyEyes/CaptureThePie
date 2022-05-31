#include <stdio.h>
#include "flag.h"

#ifdef __arm__
int dummy()
{
	asm volatile(
		"mov r0, r3\n\t"
		"pop {pc}\n\t"	
	);
}
#endif

void test()
{
	char buffer[0x80];
	printf("Alright!\nNo more printing of the flag! In fact, I'm so confident, I'll even tell you where it is and where you are now:\n0x%x\nSo can we end this now?\n", FLAG);
	gets(buffer);
	if(strcmp(buffer,"Yes")){
		printf("Still not giving in?\n");
	}
	else
	{
		printf("Ha!\n");
	}
}

int main(int argc, char **argv)
{
	test();
}
