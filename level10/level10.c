#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <malloc.h>
#include "flag.h"

#define MAX_ACCOUNTS 32

char bigBuf[0x2000];
char* flagAddr;
uint32_t pageFlags = PROT_READ;

typedef struct {
	int	super_account;
	char	username[0x20];
	char	password[0x20]; 
	char	*memo;
} account_t;

account_t *current = 0;
int numAccounts = 0;

account_t *accountList[MAX_ACCOUNTS];

void create_account()
{
	if(numAccounts>=MAX_ACCOUNTS)
	{
		printf("Can't create more accounts");
		return;
	}
	account_t *new_account = malloc(sizeof(account_t));
	new_account->super_account = 0;
	new_account->memo = NULL;
	printf("Creating account!\nWhat's the username? (32 characters max)\n");
	fgets(new_account->username,0x20,stdin);
	new_account->username[strlen(new_account->username)-1]=0;
	printf("Please set a password for the account\n");
	fgets(new_account->password,0x20,stdin);
	new_account->password[strlen(new_account->password)-1]=0;
	printf("Account created");
	accountList[numAccounts] = new_account;
	numAccounts++;
}

account_t* find_account(char* username)
{
	int i;
	for(i=0; i<numAccounts; i++)
	{
		if(!strcmp(accountList[i]->username,username))
			return accountList[i];
	}
	return NULL;
}

void set_memo()
{
	struct{
		uint32_t guard;
		uint32_t guard2;
		char buffer[0x80];
	} guarded_buffer;
	guarded_buffer.guard = 0xf7f0a000;
	guarded_buffer.guard2 = 0xf7f0a000;

	if(!current)
	{
		printf("No account selected\n");
		return;
	}
	printf("Please enter the memo:\n");
	fgets(guarded_buffer.buffer, 0x80, stdin);
	current->memo = strdup(guarded_buffer.buffer);
}

void update_memo()
{
	char buffer[0x80];
	if(!current)
	{
		printf("No account selected");
		return;
	}
	if(!current->memo)
	{
		printf("No memo to update");
		return;
	}
	printf("Please enter the memo:\n");
	fgets(current->memo, 0x80, stdin);
}

void select_account()
{
	char buffer[0x20];
	printf("Please enter the username:\n");
	fgets(buffer,0x20,stdin);
	buffer[strlen(buffer)-1]=0;
	account_t* selected = find_account(buffer);
	if(!selected)
	{
		printf("Account not found!\n");
		return;
	}
	printf("Please enter the password:\n");
	fgets(buffer, 0x20, stdin);
	buffer[strlen(buffer)-1]=0;
	if(strcmp(buffer, selected->password))
	{
		printf("Incorrect password\n");
		return;
	}
	printf("Account selected\n");
	current = selected;
}

void delete_account()
{
	if(!current)
	{
		printf("No account selected\n");
		return;
	}
	free(current->memo);
	free(current);
	current = NULL;
	printf("Account deleted!");
}

void setup_protection()
{
	size_t page_size = getpagesize();
	flagAddr = (char*)(((size_t)bigBuf+page_size)&(~(page_size-1)));
	printf("Pagesize: %d\nProtected at %p\n", page_size, flagAddr);
	mprotect(flagAddr, page_size, PROT_READ | PROT_WRITE);
	strcpy(flagAddr, FLAG);
	mprotect(flagAddr, page_size, pageFlags);
}


int main(int argc, char **argv)
{
	char buffer[0x8];
	setup_protection();
	printf("Welcome to the our account manager\n");
	printf("free_hook: 0x%p\npageFlags: 0x%p\n", &__free_hook, &pageFlags);

	while(1)
	{
		printf("\nPlease select your action\n1: Create account\n2: Select account\n3: Set Memo\n4: Delete Account\n5: Update Memo\n6: Show Account Info\n");
		fgets(buffer, 0x8, stdin);
		int choice = atoi(buffer);
		switch(choice)
		{
			case 1: create_account(); break;
			case 2: select_account(); break;
			case 3: set_memo(); break;
			case 4: delete_account(); break;
			case 5: update_memo(); break;
			default: printf("Nah"); exit(-1); return -1;
		}
	}
}
