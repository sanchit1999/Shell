#include "../shell.h"

int command_overkill(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp != 1)
	{
		printf("Invalid use of overkill\n");
		return 0;
	}
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] != 2)
		{
			status_arr[time_arr[i]] = 2;
			kill(time_arr[i], SIGKILL);
		}
	}
	return 0;
}