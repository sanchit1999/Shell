#include "../shell.h"

char * path_to_directory(char * directory)
{
	int len1 = strlen(directory), len2 = strlen(root_path), flag = 1;

	for(int i=0;i<len2;i++)
		if(directory[i] != root_path[i]) flag=0;

	if(len1<len2)
	{ 
		if(directory[0] == '/') return directory;
		else
		{
			char * temp_string = malloc(10005 * sizeof(char));
			temp_string[0] = '~';
			temp_string[1] = '/';
			for(int i=0;i<len1;i++)
				temp_string[i+2] = directory[i];
			return temp_string;
		}
	}	
	if(len1 >= len2)
	{ 
		if(!flag) return directory;
		else
		{
			if(len1==len2) return "~/";
			char * temp_string = malloc(10005 * sizeof(char));
			temp_string[0] = '~';
			for(int i=0;i<len1-len2;i++)
				temp_string[i+1] = directory[len2+i];
			return temp_string;
		}
	}	
}

void print_terminal_info()
{
	color = GREEN;
	printf("%s", color);
	printf("<%s",getenv("USER"));
    struct utsname data;
    uname(&data);
    printf("@%s", data.nodename);
    char directory[10005];
    getcwd(directory, sizeof(directory));
    color = BLUE	;
    printf("%s", color);
    printf(":%s> ",path_to_directory(directory));
    printf("%s", RESET);
}