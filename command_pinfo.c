#include "../shell.h"

int command_pinfo(char ** broken_string)
{
	int temp = 0, temp_no, status_offset = 7, memory_offset = 12;
	size_t length = 0;
	char * final_path = malloc(10005 * sizeof(char));
	while(broken_string[temp] != NULL)	temp++;	
	if(temp==1)
		temp_no = getpid();
	else
		temp_no = atoi(broken_string[1]);
	char * mem;
	char * stat_path = malloc(10005 * sizeof(char));
	sprintf(stat_path, "/proc/%d/status", temp_no);
	if(!is_regular_file(stat_path))
	{
		printf("Invalid Process\n");
		return 0;
	}
	color = BLUE;
	printf("%s", color);
	printf("pid --- %d\n\n", temp_no);
	printf("%s", RESET);
	FILE* file_descriptor = fopen(stat_path, "r");
	while(1)
	{
		if(getline(&mem, &length, file_descriptor) == -1) break;
		if(strncmp(mem, "State", 5) == 0)
		{
			color = YELLOW;
			printf("%s", color);	
			printf("Process Status --- %s\n",mem + status_offset);
			printf("%s", RESET);
		}
		if(strncmp(mem, "VmSize", 6) == 0)
		{
			color = GREEN;
			printf("%s", color);
			printf("Virtual Memory --- %s\n", mem + memory_offset);
			printf("%s", RESET);
		}
	}

	char * exe_path = malloc(1005 * sizeof(char));
	sprintf(exe_path, "/proc/%d/exe", temp_no);	
	int temp_var = readlink(exe_path, final_path, 1004);
	if(temp_var < 0)
	{
		perror("Exceutable Path(Process) --- ");
		return 0;
	}
	char * minimised_path = malloc(1010 * sizeof(char));
	final_path[temp_var] = '\0';
	int len1 = strlen(final_path);
	int len2 = strlen(root_path);
	if(len1 >= len2)
	{
		int flag = 1; 
		for(int i=0;i<len2;i++)
			if(root_path[i] != final_path[i]) flag=0;
		if(flag)
		{
			minimised_path[0] = '~';
			for(int i=len2;i<len1;i++)
				minimised_path[i-len2+1] = final_path[i];
			printf("Excexutable Path --- %s\n\n", minimised_path);
		}
		else
			printf("Excexutable Path --- %s\n\n", final_path);
	}
	else
		printf("Excexutable Path --- %s\n\n", final_path);
}