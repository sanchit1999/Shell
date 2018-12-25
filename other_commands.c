#include "../shell.h"

void other_commands(char ** broken_string)
{
	int temp = 0;
	int background = 0;
	while(broken_string[temp] != NULL) 
	{
		if(strcmp(broken_string[temp], "&") == 0) background = 1;
		temp++;
	}
	if(background == 0)
	{
		pid_t pid1, pid2;
		pid1 = fork();
		int fflag = 0;
		if(pid1 < 0)
		{
			printf("Invalid Command: Check Syntax\n");	
			exit(EXIT_FAILURE);
		}
		int var;
		if(pid1 == 0)
		{
			char ** new_string = malloc(10005 * sizeof(char *));
			temp = 0;
			int count = 0;
			for(;broken_string[temp] != NULL;temp++)
			{
				if(strcmp(broken_string[temp], "&") == 0) break;
				else
					new_string[count++] = broken_string[temp];
			}
			if(execvp(broken_string[0], new_string) == -1)
			{
				printf("Invalid Command: Check Syntax\n");
				fflag = -1;
			}
			exit(EXIT_FAILURE);
		}
		else if(fflag != -1)
		{
			fgpid = pid1;
			fgcomm = broken_string[0];
			signal(SIGINT, sigc2handler);
			signal(SIGTSTP, sigz2handler);
		    waitpid(pid1, &var, WUNTRACED);
			return;
		}	
	}
	else
	{
		pid_t pid1, pid2;
		pid1 = fork();
		if(pid1 < 0)
		{
			printf("Invalid Command: Check Syntax\n");	
			exit(EXIT_FAILURE);
		}
		int var;
		int fflag = 0;
		if(pid1 == 0)
		{
			setpgid(0,0);
			if(temp == 2 && strcmp(broken_string[0], "vi") == 0)
			{
				vi_flag = 0;
				kill(pid1, SIGSTOP);
				return;	
			}
			char ** new_string = malloc(10005 * sizeof(char *));
			temp = 0;
			int count = 0;
			for(;broken_string[temp] != NULL;temp++)
			{
				if(strcmp(broken_string[temp], "&") == 0) break;
				else
					new_string[count++] = broken_string[temp];
			}
			if(execvp(broken_string[0], new_string) == -1)
			{
				printf("Invalid Command: Check Syntax\n");
				fflag = -1;
			}
			exit(EXIT_FAILURE);
		}
		if(fflag != -1)
		{	
			pid_arr[pid1] = broken_string[0];
			status_arr[pid1] = 1;
			time_arr[curr_time++] = pid1;
		}
		return;	
	}
	return;
}