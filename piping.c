#include "../shell.h"

void piping(char ** broken_string)
{
	int fdes[2], temp = 0, var =0, r1 =0, r2 = 0;
	char * s1 = malloc(2000 * sizeof(char *));
	char * s2 = malloc(2000 * sizeof(char *));	
	while(broken_string[temp] != NULL) temp++;
	if(strcmp(broken_string[temp - 1], "|") == 0)
	{
		printf("Invalid Command : Check Syntax\n");
		return;
	}
	int arr[2000], no_pipes = 0;
	arr[0] = -1;
	for(int i=0;i<temp;i++)
	{
		if(strcmp(broken_string[i], "|") == 0)
			arr[++no_pipes] = i;
	}
	arr[++no_pipes] = temp;
	if(strcmp(broken_string[arr[1]-1], "<") == 0)
	{
		printf("Invalid use of pipes and redirection\n");
	}
	for(int j = arr[0] + 1; j <arr[1]; j++)
	{
		if(strcmp(broken_string[j], "<") == 0)
		{
			if(!is_regular_file(broken_string[j+1]))
			{
				perror("SHELL:");
				return;
			}
			r1 = 1;
			s1 = broken_string[j+1];
		}
	}
	if(strcmp(broken_string[arr[no_pipes] - 1], ">") == 0 || strcmp(broken_string[arr[no_pipes] - 1], ">>") == 0)
	{
		printf("Invalid use of pipes and redirection\n");
	}
	for(int j = arr[no_pipes -1] +1;j<arr[no_pipes];j++)
	{
		if(strcmp(broken_string[j], ">") == 0 || strcmp(broken_string[j], ">>") == 0)
		{
			if(strcmp(broken_string[j], ">") == 0)
				r2 = 1;
			else
				r2 = 2;
			s2 = broken_string[j+1];
		}
	}
	for(int i=0;i<no_pipes;i++)
	{
		char ** t_string = malloc(2000 * sizeof(char));
		int len = 0;
		for(int j=arr[i]+1;j<arr[i+1];j++)
		{
			if(strcmp(broken_string[j], "<") == 0 || strcmp(broken_string[j], ">") == 0 || strcmp(broken_string[j], ">>") == 0) break;
			t_string[len++] = broken_string[j];
		}
		t_string[len] = NULL;
		pipe(fdes);
		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			printf("Error creating child process\n");
			return;
		}
		else if(pid == 0)
		{
			if(i == 0)
		 	{
		 		if(r1 == 1)
		 		{
		 			int fd = open(s1, O_RDONLY);
		 			dup2(fd , 0);
		 			close(fd);
		 		}
				dup2(fdes[1], 1);
			}
			else if(i == no_pipes - 1)
			{
				if(r2 == 1)
				{
					int fd = open(s2, O_WRONLY | O_CREAT, 0644);
					dup2(fd , 1);
					close(fd);
				}
				else if(r2 == 2)
				{
					int fd = open(s2, O_WRONLY | O_APPEND | O_CREAT, 0644);
					dup2(fd, 1);
					close(fd);
				}
				dup2(var, 0);
			}
			else
			{	
				dup2(var, 0);
				dup2(fdes[1], 1);
			}	
			execvp(t_string[0], t_string);
			exit(0);
		}
		var = fdes[0];
		close(fdes[1]);
		waitpid(pid, NULL, 0);
	}
	return;
}