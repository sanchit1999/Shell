#include "../shell.h"

int command_pwd(char ** broken_string)
{
	char directory[2000];
	getcwd(directory, sizeof(directory));
	printf("%s\n", directory);
	return 1;
}