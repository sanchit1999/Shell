#include "../shell.h"

int command_fg(char ** broken_string)
{
	int var = 1;
	int temp = 0;
	int value = 0;
	while(broken_string[temp] != NULL) temp++;
	if(temp != 2)
	{
		printf("Invalid use of fg\n");
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
	fgpid = value;
	fgcomm = pid_arr[value];
	status_arr[value] = 2;
	signal(SIGTSTP, sigz2handler);
	signal(SIGINT, sigc2handler);
	kill(value, SIGCONT);
	int vari;
	waitpid(value, &vari, WUNTRACED);
	return 0;
}