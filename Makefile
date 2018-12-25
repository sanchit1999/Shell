shell: \
			check_type.o \
			command_cd.o \
			command_clock.o \
			command_echo.o \
			command_execute.o \
			command_ls.o \
			command_pinfo.o \
			command_pwd.o \
			command_remind.o \
			handler.o \
			other_commands.o \
			path.o \
			read.o \
			set_env.o \
			main.o \
			redirect.o \
			piping.o \
			unset_env.o \
			jobs.o \
			kjobs.o \
			fg.o \
			bg.o \
			overkill.o \
			split.o 
	gcc -g -o shell $^

clean:
	@rm -f *.o shell

main.o: shell.h main.c
	gcc -g -c main.c

kjobs.o: shell.h src/kjobs.c
	gcc -g -c src/kjobs.c	

check_type.o: shell.h src/check_type.c
	gcc -g -c src/check_type.c

jobs.o: shell.h src/jobs.c
	gcc -g -c src/jobs.c	

unset_env.o: shell.h src/unset_env.c
	gcc -g -c src/unset_env.c

overkill.o: shell.h src/overkill.c
	gcc -g -c src/overkill.c		

piping.o: shell.h src/piping.c
	gcc -g -c src/piping.c

fg.o: shell.h src/fg.c
	gcc -g -c src/fg.c		

command_cd.o: shell.h src/command_cd.c
	gcc -g -c src/command_cd.c

command_clock.o: shell.h src/command_clock.c
	gcc -g -c src/command_clock.c

command_echo.o: shell.h src/command_echo.c
	gcc -g -c src/command_echo.c

command_execute.o: shell.h src/command_execute.c
	gcc -g -c src/command_execute.c

command_ls.o: shell.h src/command_ls.c
	gcc -g -c src/command_ls.c

command_pinfo.o: shell.h src/command_pinfo.c
	gcc -g -c src/command_pinfo.c

command_pwd.o: shell.h src/command_pwd.c
	gcc -g -c src/command_pwd.c

command_remind.o: shell.h src/command_remind.c
	gcc -g -c src/command_remind.c

handler.o: shell.h src/handler.c
	gcc -g -c src/handler.c

other_commands.o: shell.h src/other_commands.c
	gcc -g -c src/other_commands.c

redirect.o: shell.h src/redirect.c
	gcc -g -c src/redirect.c	

path.o: shell.h src/path.c
	gcc -g -c src/path.c

read.o: shell.h src/read.c
	gcc -g -c src/read.c

set_env.o: shell.h src/set_env.c
	gcc -g -c src/set_env.c

bg.o: shell.h src/bg.c
	gcc -g -c src/bg.c	

split.o: shell.h src/split.c
	$(CC) -g -c src/split.c
