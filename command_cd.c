#include "../shell.h"

int command_cd(char ** broken_string)
{
	if(broken_string[1] == NULL)
		perror("SHELL");
	else
	{
		if(broken_string[1][0] == '~')
		{
			if(strlen(broken_string[1]) == 1) return chdir(root_path);
			else
			{
				char * temp_string = malloc(2000 * sizeof(char));
				int len =strlen(root_path);
				for(int i=0;i<len;i++)
					temp_string[i] = root_path[i];
				int len2 = strlen(broken_string[1]);
				for(int i=len;i<len+len2-1;i++)
					temp_string[i] = broken_string[1][i-len+1];
				temp_string[len+len2-1] = '\0';
				if(chdir(temp_string) != 0) perror("SHELL");
			}
		}
		else
			if(chdir(broken_string[1]) != 0) perror("SHELL");
	}	
}

