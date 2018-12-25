#include "../shell.h"

int command_kjob(char ** broken_string)
{
	int var = 1;
	int temp = 0;
	int value = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp != 3)
	{
		printf("Invalid use of kjobs\n");
		return 0;
	}
	int pid1 = atoi(broken_string[1]);
	int sig = atoi(broken_string[2]);
	int v = 0;
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] != 2) v++;
	}
	if(pid1 > v)
	{
		printf("Invalid job\n");
		return 0;
	}
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] == 2) continue;
		if(var == pid1)
		{
			value = time_arr[i];
			if(kill(value, sig) == -1)
			{
				perror("Invalid Signal");
				return 0;
			}
			break;
		}
		var++;
	}
	if(sig == 9)
	{
		status_arr[value] = 2;
	}
	else if(sig == 17 || sig == 19 || sig == 23)
	{
		kill(value, SIGSTOP);
		status_arr[value] = 0;
	}
	return 0;
}