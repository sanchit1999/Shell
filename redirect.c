#include "../shell.h"

int redirect(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	if(strcmp(broken_string[temp - 1], ">") == 0 || strcmp(broken_string[temp-1], "<") == 0 || strcmp(broken_string[temp-1], ">>") == 0)
	{
		printf("syntax error near unexpected token 'newline'\n");
		return 0;
	}
	for(int i=0;i<temp;i++)
	{
		if(strcmp(broken_string[i], "<") == 0)
		{
			if(broken_string[i + 1][0] == '~')
			{
				char * temp_string = malloc(2000 * sizeof(char));
				int len = strlen(root_path);
				for(int j=0;j<len;j++)
					temp_string[j] = root_path[j];
				int len2 = strlen(broken_string[i+1]);
				for(int j=len;j<len+len2-1;j++)
					temp_string[j] = broken_string[i+1][j-len+1];
				temp_string[len+len2-1] = '\0';
				if(!is_regular_file(temp_string)) 
				{
					perror("SHELL");
					return 0;
				}		
			}
			else
			{
				if(!is_regular_file(broken_string[i+1]))
				{ 
					perror("SHELL");
					return 0;
				}	
			}
		}
	}
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		int f1 = 0, f2 = 0, f3 = 0;
		char * s1 = malloc(2000 * sizeof(char));
		char * s2 = malloc(2000 * sizeof(char));
		char * s3 = malloc(2000 * sizeof(char));
		for(int i=0;i<temp;i++)
		{
			if(strcmp(broken_string[i], "<") == 0)
			{
				f1 = 1;
				if(broken_string[i + 1][0] == '~')
				{
					int len = strlen(root_path);
					for(int j=0;j<len;j++)
						s1[j] = root_path[j];
					int len2 = strlen(broken_string[i+1]);
					for(int j=len;j<len+len2-1;j++)
						s1[j] = broken_string[i+1][j-len+1];
					s1[len+len2-1] = '\0';		
				}
				else
				{
					s1 = broken_string[i+1];	
				}
			}
			if(strcmp(broken_string[i], ">") == 0)
			{
				f2 = 1;
				if(broken_string[i + 1][0] == '~')
				{
					int len = strlen(root_path);
					for(int j=0;j<len;j++)
						s2[j] = root_path[j];
					int len2 = strlen(broken_string[i+1]);
					for(int j=len;j<len+len2-1;j++)
						s2[j] = broken_string[i+1][j-len+1];
					s2[len+len2-1] = '\0';		
				}
				else
				{
					s2 = broken_string[i+1];	
				}
			}
			if(strcmp(broken_string[i], ">>") == 0)
			{
				f3 = 1;
				if(broken_string[i + 1][0] == '~')
				{
					int len = strlen(root_path);
					for(int j=0;j<len;j++)
						s3[j] = root_path[j];
					int len2 = strlen(broken_string[i+1]);
					for(int j=len;j<len+len2-1;j++)
						s3[j] = broken_string[i+1][j-len+1];
					s3[len+len2-1] = '\0';		
				}
				else
				{
					s3 = broken_string[i+1];	
				}
			}
		}
		if(f1)
		{
			int fd;
			fd = open(s1, O_RDONLY, 0);
			if(fd < 0)
			{
				printf("Unable to open input file\n");
				return 0;
			}
			dup2(fd, 0);
			close(fd);
		} 
		if(f2 && f3)
		{
			for(int j=temp;j>=0;j--)
			{
				if(strcmp(broken_string[j], ">") == 0)
				{
					f3 = 0;
					break;
				}
				else if(strcmp(broken_string[j], ">>") == 0)
				{
					f2 = 0;
					break;
				}
			}
		}
		if(f2)
		{
			int fd;
			fd = open(s2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd < 0)
			{
				printf("Unable to open output file\n");
				return 0;
			}
			dup2(fd, 1);
			close(fd);
		}
		if(f3)
		{
			int fd;
			fd = open(s3, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(fd < 0)
			{
				printf("Unable to open output file\n");
				return 0;
			}
			dup2(fd, 1);
			close(fd);	
		}
		char ** temp_str = malloc(2000 * sizeof(char *));
		int temp_val = 0;
		for(int i =0 ;i<temp;i++)
		{
			temp_val++;
			if(strcmp(broken_string[i], ">") == 0 || strcmp(broken_string[i], "<") == 0 || strcmp(broken_string[i], ">>") == 0) break;
			temp_str[i] = broken_string[i];
		} 
		if(f1)
		{
			temp_str[temp_val-1] = s1;
			temp_val ++ ;
		}
		temp_str[temp_val] = '\0';
		if(execvp(temp_str[0], temp_str) < 0)
		{
			printf("Invalid Command: Check Syntax\n");
			return 0;
		}
		return 0;
	}
	else
	{
		wait(NULL);
	}
	return 0;
}