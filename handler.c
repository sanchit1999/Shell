#include "../shell.h"

void clock_handler(int sig_num)
{
	printf("\nClock Exited\n");
	clock_run = 0;
}

int min(int a, int b)
{
	if(a<b) return a;
	return b;
}

void check_exit()
{
	int status;
	pid_t pid1 = waitpid(-1, &status, WNOHANG);
	if(pid1 > 0 && WIFEXITED(status) > 0)
	{
		status_arr[pid1] = 2;	
		fprintf(stderr, "Process %s with pid: %d exited normally\n", pid_arr[pid1], pid1);
	}
	else if(pid1 > 0 && WIFSIGNALED(status) == 1)
	{
		status_arr[pid1] = 2;	
		fprintf(stderr, "Process %s with pid: %d exited abnormally\n", pid_arr[pid1], pid1);
	}	
	return;
}

int command_exit(char ** broken_string)
{
	exit(EXIT_FAILURE);
}