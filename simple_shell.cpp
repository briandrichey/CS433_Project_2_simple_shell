#include "simple_shell.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>


#define READ_END 0 
#define WRITE_END 1

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

		if (str_token == "!!") {
			shouldSave = false;
		}
		else if (str_token == "exit") {
			shouldSave = false;
		}
		else if (str_token == "&") {
			shouldSave = false;
			shouldWait = true;
		}
		
		args[i] = token;
		i = i + 1;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;


	if (shouldSave == true) {
		//displayHistory();
		for (int i = 0; i < strlen(*args); i++) {
			//cout << args[i] << endl;
			commandHistory.push_back(args[i]);
		}
	}
}


void simple_shell::execute(char* args[]) {
	string str_args(args[0]);
	string file_name(args[2]);
	char write_msg[MAX_LINE];
 	char read_msg[MAX_LINE];
	int fd[2];

	//fork the process
	pid_t pid = fork();

	//child process will do execvp.
	if (pid == 0) {
		execvp(args[0], args);		//execvp doesnt return unless there is issue

		exit(1);	//this will only get hit if there is an issue with a command
	}
	//parent process will wait if there is an &
	else if (pid > 0) {
		if (shouldWait == true) {
			wait(NULL);
		}
		wait(NULL);		//found this line from the wait man page
		
	}
	else {
		cout << "ERROR FORKING" << endl;
		shouldRun = false;
		exit(1);
	}
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
	if(str_args == ">"){
		//int fw = open(file_name); 
		dup2(fw,1);
		}
	else if(str_args == "<"){
			
			
		}
	if(str_args == "|"){
		//translate this to our code
		/* create the pipe */
   		if (pipe(fd) == ‐1) {
     			fprintf(stderr,"Pipe failed");
     			return 1;
   		}
		 /* fork a child process */
   		pid = fork()

   		if (pid > 0) { /* parent process */
    			 /* close the unused end of the pipe */
    			 close(fd[READ_END]);
			
			//fd[WRITE_END] = open(file_name); 
			dup2(write_msg,1);

    			 /* write to the pipe */
     			write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

     			/* close the write end of the pipe */
     			close(fd[WRITE_END]);
   		}
   		else { /* child process */
     			/* close the unused end of the pipe */
     			close(fd[WRITE_END]);
			
			//fd[READ_END] = open(file_name); 
			dup2(read_msg,1);

     			/* read from the pipe */
    			 read(fd[READ_END], read_msg, MAX_LINE);
     			printf("read %s",read_msg);

     			/* close the read end of the pipe */
     			close(fd[READ_END]);
   }	

}
