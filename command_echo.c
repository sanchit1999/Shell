#include "../shell.h"

int command_echo(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL)	temp++;
	if(temp == 1)
	{
		int len = strlen(broken_string[0]);
		for(int i=5;i<len;i++)
			putchar(broken_string[0][i]);
		printf(" ");
	}
	else
	{
		if(broken_string[1][0] == '$')
		{
			char * temp = malloc(1000 * sizeof(char));
			int count = 0;
			for(int i=1;i<strlen(broken_string[1]);i++)
			{
				temp[count++] = broken_string[1][i];
			}
			if(!getenv(temp))
				printf("Non-existant");
			else	
				printf("%s", getenv(temp));
		}
		else
		{
			for(int i=1;i<temp;i++)
			{
				int len = strlen(broken_string[i]);
				for(int j=0;j<len;j++)
					putchar(broken_string[i][j]);
				printf(" ");
			}
		}	
	}	
	printf("\n");
	return 1;
}