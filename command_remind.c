#include "../shell.h"

void command_remind(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL) temp++;
	int time = atoi(broken_string[1]);
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "Forking Failed\n");
		return;
	}
	if(pid==0)
	{
		sleep(time);
		printf("\nReminder: ");
		for(int i=2;i<temp;i++)
			printf("%s ", broken_string[i]);
		printf("\n");
	}
}