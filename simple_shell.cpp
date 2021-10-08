#include "simple_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>


simple_shell::simple_shell() {
	//create shell, set shouldRun to true
	shouldRun = true;
}

void simple_shell::saveCommand(char * command[]) {
	commandHistory.push_back(*command);
}

void simple_shell::displayHistory() {
	for (int i = 0; i < commandHistory.size(); i++) {
		cout << commandHistory[i];
	}
}

/*https://stackoverflow.com/questions/12704337/splitting-a-string-with-strtok-s*/
//had to look up how strtok_s works, strtok_s is a windows specific thing that might
//need to change when we port the program
void simple_shell::tokenize(char * command[], char * args[]) {
	int i = 0;
	char* next_token = NULL;
	char* token = strtok(*command, " ");
	while (token != NULL) {
		cout << token << endl;
		args[i] = token;
		i = i + 1;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

void simple_shell::execute(char* args[]) {
	//fork the process
	//pid_t pid = fork();  

	/*child process will return a pid of 0, parent is going to be any >0 and any <0 will be error
	if (pid < 0) {
		cout << "ERROR" << endl;
		return;
	}
	else if (pid == 0) {
		cout << "CHILD FOUND" << endl;
	}
	else {
		cout << "PARENT FOUND" << endl;
	}
	*/
}

