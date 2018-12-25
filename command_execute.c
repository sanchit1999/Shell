#include "../shell.h"

int command_execute(char ** broken_string)
{
	int temp = 0;
	size_builtin_arr = 14;
	builtin_arr =  (char ** ) malloc(1000 * sizeof(char));
	builtin_arr[0] = "cd";
	builtin_arr[1] = "pwd";
	builtin_arr[2] = "echo";
	builtin_arr[3] = "pinfo";
	builtin_arr[4] = "ls";
	builtin_arr[5] = "quit";
	builtin_arr[6] = "setenv";
	builtin_arr[7] = "remindme";
	builtin_arr[8] = "unsetenv";
	builtin_arr[9] = "jobs";
	builtin_arr[10] = "kjob";
	builtin_arr[11] = "fg";
	builtin_arr[12] = "bg";
	builtin_arr[13] = "overkill";
	while(broken_string[temp] != NULL) temp++;
	if(broken_string[0]==NULL)	return EXIT_FAILURE;
	if(temp == 3 && strcmp(broken_string[0], "clock") == 0 && strcmp(broken_string[1], "-t") == 0) return command_clock(broken_string);
	int temp_size = strlen(broken_string[0]);
	for(int i=0;i<temp;i++)
	{
		if(strcmp(broken_string[i], "|") == 0) 
		{	
			piping(broken_string);
			return 0;
		}	
	}
	for(int i=0;i<temp;i++)
	{
		if(strcmp(broken_string[i], ">") == 0 || strcmp(broken_string[i], "<") == 0 || strcmp(broken_string[i], ">>") == 0) 
			return redirect(broken_string);
	}
	for(int i=0;i<size_builtin_arr;i++)
	{
		if(temp == 1 && temp_size >= 4)
		{
			if(broken_string[0][0] == 'e' && broken_string[0][1] == 'c' && broken_string[0][2] == 'h' && broken_string[0][3] == 'o')
				return command_echo(broken_string);
		}
		if(temp_size != strlen(builtin_arr[i])) continue;
		int flag = 0;
		for(int j=0;j<temp_size;j++)
			if(broken_string[0][j] != builtin_arr[i][j]) flag = 1;
		if(!flag)
		{
			switch (i)
			{
				case 0 : return command_cd(broken_string);
						 break;
				case 1 : return command_pwd(broken_string);
						 break;
				case 2 : return command_echo(broken_string);
						 break;
				case 3 : return command_pinfo(broken_string);
						 break;
				case 4 : return command_ls(broken_string);
						 break;
				case 5 : return command_exit(broken_string);
						 break;		 
				case 6 : return command_set_env(broken_string);		
						 break;
				case 7 : command_remind(broken_string);
						 return 1;
						 break;	  	
				case 8 : return command_unset_env(broken_string);
						 break;	
				case 9 : return command_jobs(broken_string);
						 break;	
				case 10 : return command_kjob(broken_string);
						 break;	
				case 11 : return command_fg(broken_string);
						 break;
				case 12 : return command_bg(broken_string);
						 break;
				case 13 : return command_overkill(broken_string);
						 break;		 	
			}
		}
	}
	other_commands(broken_string);
}