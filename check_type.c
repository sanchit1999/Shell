#include "../shell.h"

int is_regular_file(const char *path)
{
    struct stat buffer;
    stat(path, &buffer);
    return S_ISREG(buffer.st_mode);
}

int is_directory(const char *path)
{
	struct stat buffer;
	stat(path, &buffer);
	return S_ISDIR(buffer.st_mode);
}

int is_symlink(const char *path)
{
	struct stat buffer;
	lstat(path, &buffer);
	return S_ISLNK(buffer.st_mode);
}

int check_status(int pid)
{
	int status_offset = 7;
	size_t length = 0;
	char * mem;
	char * stat_path = malloc(10005 * sizeof(char));
	sprintf(stat_path, "/proc/%d/status", pid);
	FILE* file_descriptor = fopen(stat_path, "r");
	while(1)
	{
		if(getline(&mem, &length, file_descriptor) == -1) break;
		if(strncmp(mem, "State", 5) == 0)
		{	
			char * t1 = malloc(1000 * sizeof(char));
			t1 = mem + status_offset;
			if(t1[0] == 'S') return 1;
			else if(t1[0] == 'T') return 0;
			else return 2;
		}
	}

}

void sigz1handler(int sig_num)
{
	return;
}

void sigz2handler(int sig_num)
{
	kill(fgpid, 19);
	int flag = 0;
	for(int i=0;i<curr_time;i++)
	{
		if(time_arr[i] == fgpid && status_arr[fgpid] == 2)
		{
			status_arr[fgpid] = 0;
			flag = 1;
			break;
		}
	}
	if(!flag)
	{	
		time_arr[curr_time++] = fgpid;
		pid_arr[fgpid] = fgcomm;
	}
	return;
}

void sigc1handler(int sign_num)
{
	return;
}

void sigc2handler(int sig_num)
{
	kill(fgpid, SIGINT);
}