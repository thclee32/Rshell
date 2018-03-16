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
	// cout << "SOMESTRING" << endl;
	// cout << someString << endl;
	// cout << endl;

	char * cstr = new char[someString.size() + 1];
	strcpy(cstr, someString.c_str());
	char * token = strtok(cstr, " ");

	while (token != NULL) {
		exeString.push_back(token);
		token = strtok(NULL, " ");
	}

	// cout << "CONSTRUCTOR" << endl;
	// for (unsigned i = 0; i < exeString.size(); ++i) {
	// 			cout << exeString.at(i) << endl;
	// 	}
	// cout << endl;
}

Execute::Execute(vector<string> apple) {
	for (unsigned i = 0; i < apple.size(); ++i) {
		exeString.push_back(apple.at(i));
	}
}

bool Execute::execute(int in, int out)
{	
	// cout << "EXESTRING" << endl;
	// for (unsigned i = 0; i < exeString.size(); ++i) {
	// 	cout << exeString.at(i) << endl;
	// }
	// cout << endl;

	if (exeString.at(0) == "exit") {
		exit(0);
	}
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

	else {

		pid_t pid = fork();
		pid_t w;
		int status;

		if (pid < 0) { // if pid returns a negative value, then error
			cout << "*** ERROR: forking child process failed\n" << endl;
			exit(1);
		}
			
		else if (pid == 0) {
			vector<string> temp;

			// cout << "EXESTRING" << endl;
			// for (unsigned i = 0; i < exeString.size(); ++i) {
			// 	cout << exeString.at(i) << endl;
			// }
			// cout << endl;

			for (unsigned i = 0; i < exeString.size(); i++) {
				if (exeString.at(i) != "<" && exeString.at(i) != ">" && exeString.at(i) != ">>") {
					temp.push_back(exeString.at(i));
				}

				else {
					break;
				}	
			}

			// cout << "TEMP" << endl;
			// for (unsigned i = 0; i < temp.size(); ++i) {
			// 	cout << temp.at(i) << endl;
			// }
			// cout << endl;

			for (unsigned i = 0; i < exeString.size() - 1; i++) {
				if (exeString.at(i) == "<") {
					input = exeString.at(i + 1);
				}

				else if (exeString.at(i) == ">") {
					output = exeString.at(i + 1);
				}

				else if (exeString.at(i) == ">>") {
					output = exeString.at(i + 1);
				}
			}

			unsigned arrTempSize = temp.size() + 1;
			char * argTemp[arrTempSize]; 
			for (unsigned i = 0; i < arrTempSize - 1; ++i) {
				argTemp[i] = const_cast<char*>(temp.at(i).c_str());
			}
			argTemp[arrTempSize - 1] = NULL; // make last index NULL

			if (!input.empty() || !output.empty()) {
				if (!input.empty() && !output.empty()) { 
					if (find(exeString.begin(), exeString.end(), ">") != exeString.end()) { // This is the case when "<" and ">" are being used
						int fdIn = open(input.c_str(), O_RDWR);
						int fdOut = open(output.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
						
						if (fdIn == -1 || fdOut == -1)
						{
							perror("Error: unable to open file");
							return false;
						}
						
						dup2(fdIn, 0);
						dup2(fdOut, 1);
						close(fdIn);
						close(fdOut);

						//IM DYING
						//STOP DYING
					}

					else { // This is the case when "<" and ">>" are being used
						int fdIn = open(input.c_str(), O_RDWR);
						int fdOut = open(output.c_str(), O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXG);
						
						if(fdIn == -1 || fdOut == -1)
						{
							perror("Error: unable to open file");
							return false;
						}
						
						dup2(fdIn, 0);
						dup2(fdOut, 1);
						close(fdIn);
						close(fdOut);

						//IM DYING
						//STOP DYING
					}
				}

				else if (!input.empty()) { // only "<"
					int fd = open(input.c_str(), O_RDWR);
					
					if(fd == -1)
					{
						perror("Error: unable to open file");
						return false;
					}
					
					dup2(fd, 0);
					close(fd);

					//IM DYING
					//STOP DYING
				}

				else if (!output.empty()) { // only ">" or ">>"
					if (find(exeString.begin(), exeString.end(), ">") != exeString.end()) {
						int fd;		//file descriptor
						
						fd = open(output.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
						
						//if fd returns -1, it failed
						if (fd < 0)
						{
							perror("Error: open failed.");
							return false;
						}
						
						dup2(fd, 1);
						close(fd);

						//IM DYING
						//STOP DYING
					}

					else { // This means ">>" is being used
						int fd; 		//file descriptor
						
						fd = open(output.c_str(), O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG);
						//if fd returns -1, it failed
						if(fd < 0)
						{
							perror("Error: open failed.");
							return false;
						}
						
						dup2(fd, 1);
						close(fd);

						//IM DYING
						//STOP DYING
					}
				}
				dup2(in, 0);
				dup2(out, 1);

				if (in != 0) {
					close(in);
				}
				else if (out != 1) {
					close(out);
				}

				if (execvp(*argTemp, argTemp) < 0) {
					cout << "*** ERROR: exec failed\n" << endl;
					exit(1);
				}
			}
			else { // This is a normal command

				// cout << "NORMAL COMMAND" << endl;
				// for (unsigned i = 0; i < exeString.size(); ++i) {
				// 	cout << exeString.at(i) << endl;
				// }
				// cout << endl;

				char * arg[exeString.size() + 1];
				for (unsigned i = 0; i < exeString.size(); ++i) {
					arg[i] = const_cast<char*>(exeString.at(i).c_str());
				}
				arg[exeString.size()] = NULL; // make last index NULL

				dup2(in, 0);
				dup2(out, 1);

				if (in != 0) {
					close(in);
				}
				else if (out != 1) {
					close(out);
				}

				if (execvp(*arg, arg) < 0) { // if execvp returns, then error
					cout << "*** ERROR: exec failed\n" << endl;
		            exit(1);
				}
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
	
	return false;
}

bool Execute::check() {
	return true;
}