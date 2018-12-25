# Welcome to MyShell!

# Introduction to the project:
I have implemented a terminal-based shell using C language.

Owner: Sanchit Saini

## Features:
- All commands working on real terminal are working.
- current directory of shell is made home directory
- Some commands listed below are implemented separately
    - echo
    - ls
    - cd
    - pwd
    - clock (a clock appears)
    - fg
    - bg
    - jobs (shows status of background processes)
    - kjobs (sends a signal to a particular process)
    - overkill (kills all background processes)
    - pinfo (shows info of a particular process)
    - remindme (reminds user about something after sometime)
- Processes are made background processes when used '&'
- Pipes and redirection are handled properly

## Running the program:
- Go to the working directory and run `make`
- Use `./shell` to start shell

## Description of all files:
- bg.c
	- background process
	
- command_cd.c
	- cd
	
- command_clock.c
	- clock
	
- command_echo.c
	- echo
	
- command_ls.c
	- ls

- command_pinfo.c
	- pinfo

- command_pwd.c
	- pwd

- command_remind.c
	- remindme

- fg.c
	- Foreground Process
	
- jobs.c
	- jobs

- kjobs.c
	- kjobs

- other_commands.c
	- Inbuilt Commands

- overkill.c
	- overkill

- piping.c
	- Piping

- redirect.c
	- Redirection

- set_env.c
	- set_env

- unset_env.c
	- unset_env
