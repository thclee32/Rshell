#include "execute.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>	
#include <string.h>
#include <string>
#include <fcntl.h>

using namespace std;

Execute::Execute(string someString) {
	// vector<char> exeVector(someString.size()+1);
	// memcpy(&exeVector.front(), someString.c_str(), someString.size() + 1 )
	// return exeVector; // basically informally making a cstring rn to allow execvp to pass it through
	// //exeString = someString; // Will resume shortly, something came up so gtg for a bit 3:
	char * cstr = new char[someString.size() + 1];
	strcpy(cstr, someString.c_str());
	char * token = strtok(cstr, " ");

	while (token != NULL) {
		exeString.push_back(token);
		token = strtok(NULL, " ");
	}
}



bool Execute::execute()
{	
	// for(unsigned i = 0; i < exeString.size(); ++i)
	// {
	// 	cout << exeString.at(i) << endl;
	// }
	bool foundRedirect = false; //initialize flag to false
	string redirect;			//will hold the redirect symbol
	
	string temp1;
	string temp2;
	//for loop looking for redirect command
	for(unsigned i = 0; i < exeString.size(); ++i)
	{
		
		if(foundRedirect == false && (exeString.at(i) == "<" || exeString.at(i) == ">" || exeString.at(i) == ">>"))
		{
			foundRedirect = true;
			if(exeString.at(i) == "<")
			{
				redirect = "<";
			}
			if(exeString.at(i) == ">")
			{
				redirect = ">";
			}
			if(exeString.at(i) == ">>")
			{
				redirect = ">>";
			}
			i++;
		}
		if(foundRedirect == false)
		{
			temp1 = temp1 + exeString.at(i);
		}
		else
		{
			temp2 = temp2 + exeString.at(i);
		}
	}
	
	if(foundRedirect == true)
	{
		exeString.clear();
		exeString.push_back(temp1);
		exeString.push_back(temp2);
	}
	

	
	
	
	//add stuff here
	if (exeString.size() == 0) {
		return false;
	}
	if (exeString.at(0) == "exit") {
		exit(0);
	}
	
	//-----------START TEST COMMAND-----------------------------
	if (exeString.at(0) == "test" || exeString.at(0) == "[") {
		if (exeString.at(0) == "[") {
			if (exeString.at(exeString.size() - 1) != "]") {
				cout << "Incomplete brackets" << endl;
				return false;
			}
		}

		struct stat info;
		if (exeString.at(1) == "-e") {
			if (stat(const_cast<char*>(exeString.at(2).c_str()), &info) != 0) {
				cout << "unable to access " << exeString.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
		else if (exeString.at(1) == "-f") {
			if (stat(const_cast<char*>(exeString.at(2).c_str()), &info) != 0) {
				cout << "unable to access " << exeString.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else if (info.st_mode & S_IFREG) {
				cout << "(True)" << endl;
				return true;
			}
					
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		
		else if (exeString.at(1) == "-d") {
			if (stat(const_cast<char*>(exeString.at(2).c_str()), &info) != 0) {
				cout << "unable to access " << exeString.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else if (info.st_mode & S_IFDIR) {
				cout << "(True)" << endl;
				return true;
			}
					
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		
		else {
			if (stat(const_cast<char*>(exeString.at(1).c_str()), &info) != 0) {
				cout << "unable to access " << exeString.at(1) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
		
	}
	//-----------------END TEST COMMAND-------------------------
	
	
	//-----------------START REDIRECTION/PIPE COMMANDS-------------
	else if(foundRedirect) {
		//change/insert stuff here depending on how we decide to parse
		
		// cout << "here" << endl;
		// for(unsigned i = 0; i < exeString.size(); ++i)
		// {
		// 	cout << exeString.at(i) << endl;
		// }
		if(redirect == "<")
		{
			int buffer = dup(0);
			
			int outputfile = open(exeString.at(1).c_str(), O_RDWR);
			
			if(outputfile == -1)
			{
				perror("Error: unable to open file");
				return false;
			}
			
			close(0);
			dup2(outputfile, 0);
		
			//IM DYING
			//STOP DYING
			
			Execute* test = new Execute(exeString.at(0));
			bool firstcommand = test->execute();
			
			close(0);
			dup2(buffer, 0);
			
			return firstcommand;
		}
		
		// else if(redirect == "|")
		// {
		// 	int mypipe[2];
		// 	int pipereturn;
			
		// 	pipereturn = pipe(mypipe);
			
			
		// }
		
	}
	//---------------END REDIRECTION/PIPE COMMANDS------------------
	
	
	//---------------START NORMAL COMMANDS-------------------------
	else {
		char * args[exeString.size() + 1]; // make a char pointer array of the same size as cmds vector
		// populate args array with commands in cmds vector
		for (unsigned i = 0; i < exeString.size(); ++i) {
			args[i] = const_cast<char*>(exeString.at(i).c_str());
		}
		args[exeString.size()] = NULL; // make last index NULL
	
		pid_t pid = fork();
		pid_t w;
		int status;
	
		if (pid < 0) { // if pid returns a negative value, then error
			cout << "*** ERROR: forking child process failed\n" << endl;
			exit(1);
		}
		
		else if (pid == 0) {
			if (execvp(*args, args) < 0) { // if execvp returns, then error
				cout << "*** ERROR: exec failed\n" << endl;
	            exit(1);
			}
		}
		
		else {
			w = waitpid(pid, &status, 0);
			if (w == -1) {
				exit(EXIT_FAILURE);
			}
			
			if (WEXITSTATUS(status) == 0) {
				return true;
			}
		}
	}
	//---------------END NORMAL COMMANDS----------------
	
	return false;
}

bool Execute::check() {
	return true;
}