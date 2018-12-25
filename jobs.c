#include "../shell.h"

int command_jobs(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp > 1)
	{
		printf("Invalid use of jobs\n");
		return 0;
	}
	int var = 1, ty = 0;
	for(int i=1;i<curr_time;i++)
	{
		if(status_arr[time_arr[i]] == 2) continue;
		char * s1 = malloc(2000 * sizeof(char));
		if(check_status(time_arr[i]) == 1) s1 = "Running";
		else s1 = "Stopped";
		if(strcmp(pid_arr[time_arr[i]], "vi") == 0 && status_arr[time_arr[i]] != 2 && vi_flag == 0)
		{
			ty = i;
		}	
		printf("[%d]\t%s\t\t%s [%d]\n", var, s1, pid_arr[time_arr[i]], time_arr[i]);
		var++;
	}
	if(ty != 0)
	{
		status_arr[time_arr[ty]] = 2;
		printf("vi with pid: %d exited normally\n", time_arr[ty]);
		kill(SIGKILL, time_arr[ty]);
		vi_flag = 1;
	}
}