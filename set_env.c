#include "../shell.h"

int command_set_env(char ** broken_string)
{
	char * temp1 = malloc(1000 * sizeof(char));
	char * temp2 = malloc(1000 * sizeof(char));
	int x = 0, count1 = 0, count2 = 0;
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp == 2)
	{
		setenv(broken_string[1], "", 1);
		return 0;
	}
	if(temp != 3)
	{
		printf("Invalid Command: Check Syntax\n");
		return 0;
	}
    if(temp == 3)
	{
		temp1 = broken_string[1];
		temp2 = broken_string[2];
	}
	setenv(temp1, temp2, 1);
	return 1;
}