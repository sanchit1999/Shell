#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include "shell.h"

int main(int argc, char *argv[])
{
	pid_arr = (char ** )malloc(100000 * sizeof(char*));
	status_arr = (int *)malloc(100000 * sizeof(int));
	time_arr = (int *)malloc(100000 * sizeof(int));
	curr_time = 1;
	root_path = getenv("PWD");
	while(1)
	{
		signal(SIGTSTP, sigz1handler);
		signal(SIGINT, sigc1handler);
		print_terminal_info();
		char * commands =  read_command();
		char ** broken_commands = split_commands(commands);
		int line = 0;
		while(1)
		{
			check_exit();
			if(broken_commands[line] == NULL) break;
			char ** broken_string = split_flags(broken_commands[line]);
			int val = command_execute(broken_string);
			free(broken_string);
			line++;
		}
	}
}