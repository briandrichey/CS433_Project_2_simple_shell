#include "simple_shell.h"
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

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

void simple_shell::tokenize(char * command[], char * args[]) {

}

void simple_shell::execute(char* args[]) {
	//fork the process
	pid_t pid = fork();

}

