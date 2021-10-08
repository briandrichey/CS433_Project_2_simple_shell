#pragma once
#include <vector>


using namespace std;

class simple_shell {
public:
	simple_shell();

	bool shouldRun;
	void tokenize(char * command[], char * args[]);	 //turn command into a list of args[]
	void execute(char * args[]);						//execute command based on args list
	void saveCommand(char * command[]);
	void displayHistory();

private:
	vector<char*> commandHistory;

};