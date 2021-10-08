#include <stdio.h>
#include <iostream>
#include "simple_shell.h"

#define MAX_LINE 80

int main() {
	simple_shell osh; //sets shouldRun to true on creation

	char * commands = new char[MAX_LINE];	
	char * args = new char[MAX_LINE / 2 + 1];

	/*
	* After reading user input, steps are: 
	* 1- fork a child process using fork()
	* 2- the child process will invoke execvp()
	* 3- parent will invoke wait() UNLESS the command included &
	*/
	while (osh.shouldRun) {							/*!DONT FORGET TO SET OSH.SHOULDRUN TO FALSE, EVENTUALLY!*/
		cout << "osh> ";
		cout.flush();

		cin.getline(commands, MAX_LINE);

		osh.tokenize(&commands, &args);	//this constructs args[] for execvp

		osh.execute(&args);
		//after we have the args[] set up such that args[0] = command, args[1] = parameters, and args[2] = NULL
		//within parameters will be things such as the "-l" in "ls -l", filename if >> / << is used, "&" for putting things to background
		
		//osh.shouldRun = false;
	}


	return 0;
}