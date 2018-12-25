#include "../shell.h"

int command_bg(char ** broken_string)
{
	int var = 1;
	int temp = 0;
	int value = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp != 2)
	{
		printf("Invalid use of bg\n");
		return 0;
	}
	int pid1 = atoi(broken_string[1]);
	int v = 0;
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] != 2) v++;
	}
	if(pid1 > v)
	{
		printf("Invalid process\n");
		return 0;
	}
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] == 2) continue;
		if(var == pid1)
		{
			value = time_arr[i];
			break;
		}
		var++;
	}
	if(kill(value, SIGCONT) == -1)
	{
		perror("Error");
	}
	return 0;
}