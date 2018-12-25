#include "../shell.h"

int command_ls(char ** broken_string)
{
	int temp = 0;
	while(broken_string[temp] != NULL)	temp++;
	if(temp == 1)
	{
		char directory[2000];
		getcwd(directory, sizeof(directory));
		DIR * temp_dir;
		struct dirent *temp_file;
		temp_dir = opendir(directory);
		while(1)
		{
			temp_file = readdir(temp_dir);
			if(temp_file == NULL) break;
			if(temp_file -> d_name[0] != '.')
			{
				if(is_directory(temp_file -> d_name))
				{
					color = BLUE;
				}	
				else if(is_regular_file(temp_file -> d_name))
				{
					struct stat buffer;
					stat(temp_file -> d_name, &buffer);
					if(buffer.st_mode & S_IXUSR)
					{
						color = GREEN;
					}
					else
					{
						color = RESET;
					}
				}
				else
				{
					color = YELLOW;
				}
				printf("%s  ", temp_file -> d_name);
			}
		}
		printf("%s", RESET);
		printf("\n");
		closedir(temp_dir);
	}
	else
	{	
		int flagl = 0;
		int flaga = 0;
		int flag  = 0;
		int g = 0;
		for(int i=1;i<temp;i++)
		{
			if(broken_string[i][0] == '-')
			{
				int len = strlen(broken_string[i]);
				for(int j=1;j<len;j++)
				{
					if(broken_string[i][j] == 'a') flaga = 1;
					else if(broken_string[i][j] == 'l') flagl = 1;
					else flag = 1;
				}
				if(flag)
				{
					printf("Invalid Command: Check Syntax\n");
					break;
				}
			}
			else g++;
		}
		if(flag) return 0;
		if(!flagl)
		{	
			if(flaga && temp==2)
			{
				char directory[2000];
				getcwd(directory, sizeof(directory));
				DIR * temp_dir;
				struct dirent *temp_file;
				temp_dir = opendir(directory);
				printf("%s", color);
				while(1)
				{
					temp_file = readdir(temp_dir);
					if(temp_file == NULL) break;
					printf("%s  ", temp_file -> d_name);
				}
				printf("%s", RESET);
				printf("\n");
				closedir(temp_dir);
			}
			else
			{
				for(int i=1;i<temp;i++)
				{	
					if(broken_string[i][0] == '-') continue;
					if(is_regular_file(broken_string[i]))
					{
						struct stat buffer;
					    stat(broken_string[i], &buffer);
					    if(buffer.st_mode & S_IXUSR)
					    {
					    	color = GREEN;
					    	printf("%s", color);
					    }
						printf("%s\n", broken_string[i]);
						printf("%s", RESET);
						continue;
					}
					if(is_symlink(broken_string[i]))
					{
						color = RED;
						printf("%s", color);
						printf("%s\n", broken_string[i]);
						printf("%s", RESET);
						continue;	
					}
					DIR * temp_dir;
					struct dirent *temp_file;
					char * temp_string = malloc(2000 * sizeof(char));
					if(temp != 2)
					{
						color = BLUE;
						printf("%s", color);
						printf("%s:\n", broken_string[i]);
						printf("%s", RESET);
					}
					if(broken_string[i][0] == '~')
					{
						int len = strlen(root_path);
						for(int j=0;j<len;j++)
							temp_string[j] = root_path[j];
						int len2 = strlen(broken_string[i]);
						if(len2 >= 3)
						{
							for(int j=len+1;j<len2+len;j++)
								temp_string[j-1] = broken_string[i][j-len];
						}	
						temp_string[len+len2-1] = '\0';
					}
					else
						temp_string =  broken_string[i];

					if(!is_directory(temp_string))
					{
						perror("ls");
						continue;
					}
					temp_dir = opendir(temp_string);
					while(1)
					{						
						temp_file = readdir(temp_dir);
						if(temp_file == NULL) break;
						if(!flaga)
						{
							if(temp_file -> d_name[0] != '.')	
								printf("%s  ", temp_file -> d_name);
						}
						else
							printf("%s\n", temp_file -> d_name);
					}
					if(i == temp-1)
						printf("\n");
					else
						printf("\n\n");
					closedir(temp_dir);
				}
			}		
		}
		else
		{
			struct stat buffer;
			struct stat lbuffer;
			struct passwd *buffer_user;
			struct group *buffer_group;
			time_t curr_time;
			struct tm *s_time;

			if(temp == 2 || (g == 0 && flagl && flaga) )
			{
				char directory[2000];
				getcwd(directory, sizeof(directory));
				DIR * temp_dir;
				struct dirent *temp_file;
				temp_dir = opendir(directory);
				
				while(1)
				{
					temp_file = readdir(temp_dir);
					if(temp_file == NULL) break;

					char * var = malloc(2000 * sizeof(char));
					sprintf(var, "%s/%s", directory, temp_file -> d_name);

					stat(var, &buffer);
					lstat(var, &lbuffer);

					if(!flaga && temp_file -> d_name[0] == '.') continue;

					if(is_symlink(var))
					{
						printf("l");

						if(lbuffer.st_mode & S_IRUSR)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWUSR)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXUSR)
							printf("x");
						else
							printf("-");
						if(lbuffer.st_mode & S_IRGRP)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWGRP)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXGRP)
							printf("x");
						else
							printf("-");
						if(lbuffer.st_mode & S_IROTH)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWOTH)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXOTH)
							printf("x");
						else
							printf("-");
						
						printf("\t%d", (int) lbuffer.st_nlink);
						buffer_user = getpwuid(lbuffer.st_uid);
						printf("\t%s", buffer_user -> pw_name);
						buffer_group = getgrgid(lbuffer.st_uid);
						printf("\t\t%s", buffer_group -> gr_name);
						printf("\t\t%lld", (long long int)lbuffer.st_size);
						char * date = malloc(500 * sizeof(char));
						time(&curr_time);
						s_time = localtime(&lbuffer.st_ctime);
						strftime(date, 500, "%a %b %e %Y %R",s_time);
						printf("\t\t%s", date);
						color = RED;
						printf("%s", color);
						printf("\t\t%s", temp_file -> d_name);
						printf("%s", RESET);
						printf("\n");			

					}
					else if(is_regular_file(var) || is_directory(var))
					{
						if(is_directory(var)) 
							printf("d");
						else
							printf("-");

						if(buffer.st_mode & S_IRUSR)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWUSR)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXUSR)
							printf("x");
						else
							printf("-");
						if(buffer.st_mode & S_IRGRP)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWGRP)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXGRP)
							printf("x");
						else
							printf("-");
						if(buffer.st_mode & S_IROTH)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWOTH)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXOTH)
							printf("x");
						else
							printf("-");
						
						printf("\t%d", (int) buffer.st_nlink);
						buffer_user = getpwuid(buffer.st_uid);
						printf("\t%s", buffer_user -> pw_name);
						buffer_group = getgrgid(buffer.st_uid);
						printf("\t\t%s", buffer_group -> gr_name);
						printf("\t\t%lld", (long long int)buffer.st_size);
						char * date = malloc(500 * sizeof(char));
						time(&curr_time);
						s_time = localtime(&buffer.st_ctime);
						strftime(date, 500, "%a %b %e %Y %R",s_time);
						printf("\t\t%s", date);
						if(is_directory(var))
						{
							color = BLUE;
						}
						else
						{
							if(buffer.st_mode & S_IXUSR)
							{
								color = GREEN;
							}
							else
							{
								color = RESET;
							}
						}
						printf("%s", color);
						printf("\t\t%s", temp_file -> d_name);
						printf("%s", RESET);
						printf("\n");
					}

				}
				printf("\n");
				closedir(temp_dir);
			}
			else
			{
				for(int i=1;i<temp;i++)
				{
					if(broken_string[i][0] == '-') continue;
					if(is_regular_file(broken_string[i]))
					{
						stat(broken_string[i], &buffer);
						if(buffer.st_mode & S_IXUSR)
						{
							color = GREEN;
						}
						else
						{
							color = RESET;
						}
						printf("%s", color);
						printf("\n%s\n", broken_string[i]);
						printf("%s", RESET);
						printf("-");
						if(buffer.st_mode & S_IRUSR)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWUSR)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXUSR)
							printf("x");
						else
							printf("-");
						if(buffer.st_mode & S_IRGRP)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWGRP)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXGRP)
							printf("x");
						else
							printf("-");
						if(buffer.st_mode & S_IROTH)
							printf("r");
						else
							printf("-");
						if(buffer.st_mode & S_IWOTH)
							printf("w");
						else
							printf("-");
						if(buffer.st_mode & S_IXOTH)
							printf("x");
						else
							printf("-");
						
						printf("\t%d", (int) buffer.st_nlink);
						buffer_user = getpwuid(buffer.st_uid);
						printf("\t%s", buffer_user -> pw_name);
						buffer_group = getgrgid(buffer.st_uid);
						printf("\t\t%s", buffer_group -> gr_name);
						printf("\t\t%lld", (long long int)buffer.st_size);
						char * date = malloc(500 * sizeof(char));
						time(&curr_time);
						s_time = localtime(&buffer.st_ctime);
						strftime(date, 500, "%a %b %e %Y %R",s_time);
						printf("\t\t%s", date);
						printf("%s", color);
						printf("\t\t%s", broken_string[i]);
						printf("%s", RESET);
						printf("\n");
						continue;
					}
					if(is_symlink(broken_string[i]))
					{
						color = YELLOW;
						printf("\n%s\n", broken_string[i]);
						lstat(broken_string[i], &lbuffer);
						printf("l");
						if(lbuffer.st_mode & S_IRUSR)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWUSR)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXUSR)
							printf("x");
						else
							printf("-");
						if(lbuffer.st_mode & S_IRGRP)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWGRP)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXGRP)
							printf("x");
						else
							printf("-");
						if(lbuffer.st_mode & S_IROTH)
							printf("r");
						else
							printf("-");
						if(lbuffer.st_mode & S_IWOTH)
							printf("w");
						else
							printf("-");
						if(lbuffer.st_mode & S_IXOTH)
							printf("x");
						else
							printf("-");
						
						printf("\t%d", (int) lbuffer.st_nlink);
						buffer_user = getpwuid(lbuffer.st_uid);
						printf("\t%s", buffer_user -> pw_name);
						buffer_group = getgrgid(lbuffer.st_uid);
						printf("\t\t%s", buffer_group -> gr_name);
						printf("\t\t%lld", (long long int)lbuffer.st_size);
						char * date = malloc(500 * sizeof(char));
						time(&curr_time);
						s_time = localtime(&lbuffer.st_ctime);
						strftime(date, 500, "%a %b %e %Y %R",s_time);
						printf("\t\t%s", date);
						printf("%s", color);
						printf("\t\t%s", broken_string[i]);
						printf("%s", RESET);
						printf("\n");
						continue;
					}
					DIR * temp_dir;
					struct dirent *temp_file;
					char * temp_string = malloc(2000 * sizeof(char));

					if(temp != 2)
						printf("\n%s:\n", broken_string[i]);
					if(broken_string[i][0] == '~')
					{
						int len = strlen(root_path);
						for(int j=0;j<len;j++)
							temp_string[j] = root_path[j];
						int len2 = strlen(broken_string[i]);
						if(len2 >= 3)
						{
							for(int j=len+1;j<len2+len;j++)
								temp_string[j-1] = broken_string[i][j-len];
						}	
						temp_string[len+len2-1] = '\0';
					}
					else
						temp_string =  broken_string[i];

					if(!is_directory(temp_string))
					{
						perror("ls");
						continue;
					}
					temp_dir = opendir(temp_string);

					while(1)
					{
						temp_file = readdir(temp_dir);
						if(temp_file == NULL) break;

						char * var = malloc(2000 * sizeof(char));
						sprintf(var, "%s/%s", temp_string, temp_file -> d_name);

						stat(var, &buffer);
						lstat(var, &lbuffer);

						if(!flaga && temp_file -> d_name[0] == '.') continue;

						if(is_symlink(var))
						{
							printf("l");
							if(lbuffer.st_mode & S_IRUSR)
								printf("r");
							else
								printf("-");
							if(lbuffer.st_mode & S_IWUSR)
								printf("w");
							else
								printf("-");
							if(lbuffer.st_mode & S_IXUSR)
								printf("x");
							else
								printf("-");
							if(lbuffer.st_mode & S_IRGRP)
								printf("r");
							else
								printf("-");
							if(lbuffer.st_mode & S_IWGRP)
								printf("w");
							else
								printf("-");
							if(lbuffer.st_mode & S_IXGRP)
								printf("x");
							else
								printf("-");
							if(lbuffer.st_mode & S_IROTH)
								printf("r");
							else
								printf("-");
							if(lbuffer.st_mode & S_IWOTH)
								printf("w");
							else
								printf("-");
							if(lbuffer.st_mode & S_IXOTH)
								printf("x");
							else
								printf("-");
							
							printf("\t%d", (int) lbuffer.st_nlink);
							buffer_user = getpwuid(lbuffer.st_uid);
							printf("\t%s", buffer_user -> pw_name);
							buffer_group = getgrgid(lbuffer.st_uid);
							printf("\t\t%s", buffer_group -> gr_name);
							printf("\t\t%lld", (long long int)lbuffer.st_size);
							char * date = malloc(500 * sizeof(char));
							time(&curr_time);
							s_time = localtime(&lbuffer.st_ctime);
							strftime(date, 500, "%a %b %e %Y %R",s_time);
							printf("\t\t%s", date);
							color = YELLOW;
							printf("%s", color);
							printf("\t\t%s", temp_file -> d_name);
							printf("%s", RESET);
							printf("\n");			

						}
						else if(is_regular_file(var) || is_directory(var))
						{
							if(is_directory(var)) 
								printf("d");
							else
								printf("-");

							if(buffer.st_mode & S_IRUSR)
								printf("r");
							else
								printf("-");
							if(buffer.st_mode & S_IWUSR)
								printf("w");
							else
								printf("-");
							if(buffer.st_mode & S_IXUSR)
								printf("x");
							else
								printf("-");
							if(buffer.st_mode & S_IRGRP)
								printf("r");
							else
								printf("-");
							if(buffer.st_mode & S_IWGRP)
								printf("w");
							else
								printf("-");
							if(buffer.st_mode & S_IXGRP)
								printf("x");
							else
								printf("-");
							if(buffer.st_mode & S_IROTH)
								printf("r");
							else
								printf("-");
							if(buffer.st_mode & S_IWOTH)
								printf("w");
							else
								printf("-");
							if(buffer.st_mode & S_IXOTH)
								printf("x");
							else
								printf("-");
							
							printf("\t%d", (int) buffer.st_nlink);
							buffer_user = getpwuid(buffer.st_uid);
							printf("\t%s", buffer_user -> pw_name);
							buffer_group = getgrgid(buffer.st_uid);
							printf("\t\t%s", buffer_group -> gr_name);
							printf("\t\t%lld", (long long int)buffer.st_size);
							char * date = malloc(500 * sizeof(char));
							time(&curr_time);
							s_time = localtime(&buffer.st_ctime);
							strftime(date, 500, "%a %b %e %Y %R",s_time);
							printf("\t\t%s", date);
							if(is_directory(var))
							{
								color = BLUE;
							}
							else
							{
								if(buffer.st_mode & S_IXUSR)
								{
									color = GREEN;
								}
								else
								{
									color = RESET;
								}
							}
							printf("%s", color);
							printf("\t\t%s", temp_file -> d_name);
							printf("%s", RESET);
							printf("\n");
						}

					}
					if(i == temp-1)
						printf("\n");
					else
						printf("\n\n");
					closedir(temp_dir);
				}
			}
		}		
	}
}