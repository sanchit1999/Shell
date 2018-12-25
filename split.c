#include "../shell.h"

char ** split_commands(char * buffer)
{
	int buffer_length = 200, pos = 0;
	char ** commands = (char **) malloc(sizeof(char*) * buffer_length);
	if(!commands)
	{
		write(1, "Allocation Error\n", 17);
		exit(EXIT_FAILURE);
	}
	char * delim = ";";
	char * temp = strtok(buffer, delim);
	while(1)
	{
		if(temp == NULL) break;
		commands[pos] = temp;
		pos++;
		temp = strtok(NULL, delim);
		if(pos >= buffer_length)
		{
			buffer_length += 200;
			commands = (char **) realloc(commands, sizeof(char*) * buffer_length);
			if(!commands)
			{
				write(1, "Allocation Error\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
	commands[pos] = NULL;
	return commands;
}

char ** split_flags(char * buffer)
{
	int buffer_length = 200, pos = 0;
	char ** commands = (char **) malloc(sizeof(char*) * buffer_length);
	if(!commands)
	{
		write(1, "Allocation Error\n", 17);
		exit(EXIT_FAILURE);
	}
	int flag = 0, len = strlen(buffer);
	if(len >= 4 && buffer[0] == 'e' && buffer[1] == 'c' && buffer[2] == 'h' && buffer[3] == 'o')
	{
		for(int i=4;i<len;i++)
		{
			if(buffer[i] != ' ')
			{
				if(buffer[i] == '\"')
				{
					flag = 1;
					break;
				}	
			}
		}
		if(flag == 1)
		{
			commands[0] = buffer;
			commands[1] = NULL;
			return commands;
		}	
	}
	char * delim = " \n\t\r\v\f";
	char * temp = strtok(buffer, delim);
	while(1)
	{
		if(temp == NULL) break;
		commands[pos] = temp;
		pos++;
		temp = strtok(NULL, delim);
		if(pos >= buffer_length)
		{
			buffer_length += 200;
			commands = (char **) realloc(commands, sizeof(char*) * buffer_length);
			if(!commands)
			{
				write(1, "Allocation Error\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
	commands[pos] = NULL;
	return commands;
}