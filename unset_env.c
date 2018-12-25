#include "../shell.h"
int command_unset_env(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp != 2)
	{
		printf("Invalid Command: Check Syntax\n");
		return 0;
	}
	unsetenv(broken_string[1]);
}