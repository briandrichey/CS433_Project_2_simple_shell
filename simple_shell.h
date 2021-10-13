#pragma once
#include <vector>
#include <string.h>

#define MAX_LINE 80

using namespace std;

class simple_shell {
public:
	simple_shell();

	bool shouldRun;
	bool shouldWait;
	void tokenize(char command[], char * args[]);	 //turn command into a list of args[]
	void execute(char * args[]);						//execute command based on args list
	void displayHistory();

private:
	vector<char*> commandHistory;
};