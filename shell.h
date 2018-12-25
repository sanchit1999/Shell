#ifndef DEFINITIONS
#define DEFINITIONS

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

char ** builtin_arr;
int size_builtin_arr;
char * root_path;
char ** pid_arr;
int * status_arr;
int * time_arr;
int clock_run;
int run;
char * color;
int curr_time;
int fgpid;
char * fgcomm;
int vi_flag;

void clock_handler(int sig_num);

int min(int a, int b);

void check_exit();

int command_set_env(char ** broken_string);

void command_remind(char ** broken_string);

int command_clock(char ** broken_string);

int is_regular_file(const char *path);

int is_directory(const char *path);

int is_symlink(const char *path);

int command_pinfo(char ** broken_string);

void other_commands(char ** broken_string);

int command_cd(char ** broken_string);

int command_pwd(char ** broken_string);

int command_echo(char ** broken_string);

int command_ls(char ** broken_string);

int command_exit(char ** broken_string);

int command_execute(char ** broken_string);

char * path_to_directory(char * directory);

char ** split_commands(char * buffer);

char ** split_flags(char * buffer);

char * read_command();

void print_terminal_info();

int redirect(char ** broken_string);

void piping(char ** broken_string);

int command_unset_env(char ** broken_string);

int command_jobs(char ** broken_string);

int command_kjob(char ** broken_string);

int command_fg(char ** broken_string);

int command_bg(char ** broken_string);

int command_overkill(char ** broken_string);

int check_status(int pid);

void sigz1handler(int sig_num);

void sigz2handler(int sig_num);

void sigc1handler(int sig_num);

void sigc2handler(int sig_num);

#endif