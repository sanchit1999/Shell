#include "../shell.h"

int command_clock(char ** broken_string)
{
	clock_run = 1;
	int time = atoi(broken_string[2]);
	char * file1 = malloc(1005 * sizeof(char));
	char * file2 = malloc(1005 * sizeof(char));
	sprintf(file1, "/sys/class/rtc/rtc0/date");
	sprintf(file2, "/sys/class/rtc/rtc0/time");
	size_t len1 = 0, len2 = 0;
	signal(SIGINT,clock_handler);
	while(clock_run)
	{
		FILE * fd1 = fopen(file1, "r");
		FILE * fd2 = fopen(file2, "r");
		char * mem1;
		char * mem2;
		getline(&mem1, &len1, fd1);
		getline(&mem2, &len2, fd2);
		char * out1 = malloc(40 * sizeof(char));
		char * out2 = malloc(40 * sizeof(char));
		for(int i=0;i<11;i++)
		{
			out1[i] = mem1[i];
			out2[i] = mem2[i];
		}
		out1[10] = '\0';
		out2[8] = '\0';	
		printf("%s, ", out1);
		printf("%s\n\n", out2);
		sleep(time);
	}
	clock_run = 1;
}