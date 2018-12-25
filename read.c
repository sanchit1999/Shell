#include "../shell.h"

char * read_command()
{
	int command_length = 2000, curr_pos = 0;
	char * buffer;
	char curr_char;
	buffer = (char *) malloc(sizeof(buffer)*(command_length));
	if(! buffer)
	{
		write(1, "Allocation Error\n", 17);
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		curr_char = getchar();
		if(curr_char == '\n' || curr_char == EOF)
		{
			buffer[curr_pos] = '\0';
			return buffer;  
		}
		buffer[curr_pos++] = curr_char;
		if(curr_pos >= command_length)
		{
			command_length += 2000;
			buffer = realloc(buffer, command_length);
			if(! buffer)
			{
				write(1, "Allocation Error\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
}