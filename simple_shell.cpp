#include "simple_shell.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>



simple_shell::simple_shell() {
	shouldRun = true;
	shouldWait = false;
}

void simple_shell::displayHistory() {
	for (int i = 0; i < commandHistory.size(); i++) {
		cout << "Command history: " << i << " " << commandHistory[i] << endl;
	}
}


void simple_shell::tokenize(char command[], char* args[]) {
	int i = 0;
	bool shouldSave = true;
	char* token = strtok(command, " ");

	while (token != NULL) {
		string str_token(token);

		if (str_token == "&") {
			shouldSave = false;
			shouldWait = true;
		}
		else if (str_token == ">") {
		
		}
		else if (str_token == "<") {

		}
		
		args[i] = token;
		i = i + 1;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;


	if (shouldSave == true) {
		//displayHistory();
		//for (int i = 0; i < strlen(*args); i++) {
			//cout << args[i] << endl;
			//commandHistory.push_back(args[i]);
		//}
	}
}


void simple_shell::execute(char* args[]) {
	string str_args(args[0]);
	int fd[2];

	if (str_args == "exit") {
		shouldRun = false;
		return;
	}

	/*history functionality*/
	if (str_args == "!!") {
		if (!commandHistory.empty()) {			
			strcpy(*args, commandHistory.back()); 		
			commandHistory.pop_back();
		}
		else {
			cout << "No commands in history!" << endl;
			return;
		}
	}

	/*
	if (str_args == ">") {
		int fw = open(str_args[3]);
		dup2(fw, 1);
	}
	*/

	
	pid_t pid = fork();						//fork the process

		
	if (pid == 0) {							//child process will do execvp.
		execvp(args[0], args);		

		exit(1);							//this will only get hit if there is an issue with a command
	}
	
	else if (pid > 0) {						//parent process will wait if there is an &
		
		wait(NULL);							//for now parent just waits for child
	
	}
	else {
		cout << "ERROR FORKING" << endl;
		shouldRun = false;
		exit(1);
	}
}