#include "../shell.h"

void manage()
{
	signal(SIGTSTP, sigz1handler);
	while(1)
	{
		print_terminal_info();
		char * commands =  read_command();
		char ** broken_commands = split_commands(commands);
		int line = 0;
		while(1)
		{
			check_exit();
			if(broken_commands[line] == NULL) break;
			char ** broken_string = split_flags(broken_commands[line]);
			if(strcmp(broken_string[0],"quit") == 0)
			{
				exit(EXIT_FAILURE);
			}
			int val = command_execute(broken_string);
			free(broken_string);
			line++;
		}
	}
}