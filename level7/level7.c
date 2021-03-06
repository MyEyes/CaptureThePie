#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flag.h"

#define MAX_ACCOUNTS 32

char name[0x80];

typedef struct {
	int	super_account;
	char	*memo;
	char	username[0x20];
	char	password[0x20]; 
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
	printf("Please set a password for the account\n");
	fgets(new_account->password,0x20,stdin);
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
	char buffer[0x80];
	if(!current)
	{
		printf("No account selected");
		return;
	}
	printf("Please enter the memo:\n");
	fgets(buffer, 0x80, stdin);
	current->memo = strdup(buffer);
}

void select_account()
{
	char buffer[0x20];
	printf("Please enter the username:\n");
	fgets(buffer,0x20,stdin);
	account_t* selected = find_account(buffer);
	if(!selected)
	{
		printf("Account not found!\n");
		return;
	}
	printf("Please enter the password:\n");
	fgets(buffer, 0x20, stdin);
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

void show_flag()
{
	if(!current)
	{
		printf("No account selected\n");
		return;
	}
	if(!current->super_account)
	{
		printf("Only super users can see the flag!\n");
		return;
	}
	printf(FLAG);
}

void show_debug()
{
	if(!current)
	{
		printf("No account selected\n");
		return;
	}
	printf("Account:\n\tLocation: %x\n\tSuper: %d\n\tName: %s\n\tMemo: %x\n", current, current->super_account, current->username, current->memo);
}


int main(int argc, char **argv)
{
	char buffer[0x8];
	printf("Welcome to the debug version of our account manager\n");
	while(1)
	{
		printf("\nPlease select your action\n1: Create account\n2: Select account\n3: Set Memo\n4: Delete Account\n5: Show Flag\n6: Show Account Debug\n");
		fgets(buffer, 0x8, stdin);
		int choice = atoi(buffer);
		switch(choice)
		{
			case 1: create_account(); break;
			case 2: select_account(); break;
			case 3: set_memo(); break;
			case 4: delete_account(); break;
			case 5: show_flag(); break;
			case 6: show_debug(); break;
			default: printf("Nah"); exit(-1);
		}
	}
}
