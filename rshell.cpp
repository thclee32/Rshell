// this is the rshell.cpp, where to implement rshell stuff, aka parsing and such
#include "rshell.h"
#include <iostream>

using namespace std;


Base* shunting_yard(vector<string> &cmdVector) {
	
	stack<string>cmdStack; //stack that stores the operands
	queue<string> cmdQueue; //queue that stores the commands
	for (unsigned int i = 0; i < cmdVector.size(); i++) {
			if (cmdVector.at(i) != ";" && cmdVector.at(i) != "|" && cmdVector.at(i) != "&" && cmdVector.at(i) != "(" && cmdVector.at(i) != ")") {
				//cout << "its a command" << endl;
				cmdQueue.push(cmdVector.at(i));
			}
			else if (cmdVector.at(i) == ";" || cmdVector.at(i) == "|" || cmdVector.at(i) == "&") 
			{ 
				if (cmdStack.empty()) {
					//cout << "because stack is empty" << endl;
					cmdStack.push(cmdVector.at(i));
					continue;
				}
				
				else if (cmdStack.top() != "(") { //stupid while loop wikipedia actually lied
					//cout << "if ( dozen exist" << endl; // baited, also wait if ( dozen? don't you mean doesn't?) we can take out the comments now
					cmdQueue.push(cmdStack.top());
					cmdStack.pop();
				}
				
				//cout << "pushing the connector" << endl;
				cmdStack.push(cmdVector.at(i));
			}
			
			else if (cmdVector.at(i) == "(") {
				//cout << "if it is left" << endl;
				cmdStack.push(cmdVector.at(i));
			}
			
			else if (cmdVector.at(i) == ")") {
				//cout << "beginning of while loop" << endl;
				while (cmdStack.top() != "(") {
					cmdQueue.push(cmdStack.top());
					cmdStack.pop();// might be here? oh so its cmdStack leggo back to fb
				}
				//cout << "popping the left one" << endl;
				cmdStack.pop();// or here?
			}
	}
	
	while (!cmdStack.empty()) {
				cmdQueue.push(cmdStack.top());
				cmdStack.pop();
	}
	
	stack<Base*> theStack;
	
	while (!theStack.empty()) {
			theStack.pop(); 
	}
	
	Base* B;
	
	while (!cmdQueue.empty()) {
		if (cmdQueue.front() == "&") { 
			B = new And(); 
		}
		
		else if (cmdQueue.front() == "|") { 
			B = new Or();
		}
		
		else if (cmdQueue.front() == ";") { 
			B = new Semi();
		}
		
		else { 
			B = new Execute(cmdQueue.front());
		}
		
		if (B->check()) {
				theStack.push(B);
		}
		else {
			Base* rhs = theStack.top();
			theStack.pop();
			Base* lhs = theStack.top();
			theStack.pop();
			B->set(lhs, rhs);
			theStack.push(B);
		}
			
		cmdQueue.pop();
	}

	Base* start = theStack.top();
	while (!theStack.empty()) {
			theStack.pop();
	}
	return start;
	//return cmdQueue;
}

/*vector<string> parse(string userCmd) {
	
	char * cstr = new char[userCmd.size() + 1];
	strcpy(cstr, userCmd.c_str());
	char * token = strtok(cstr, " ");

	vector<string> commands;
	while (token != NULL) {
		commands.push_back(token);
		token = strtok(NULL, " ");
	}
	
	for */
	
void parse(string userCmd, vector<string> &combined) { //parses input and puts it into vector
	
	bool ConnectorTrue = false; //connector flag
	bool CommentTrue = false; //comment flag
	int start = 0; //marker for substring
	
	for (unsigned i = 0; i < userCmd.size(); i++) { //traversing to check for a comment
		if (userCmd.at(i) == '#') {
			CommentTrue = true; //if it finds the comment, it'll flag it true
			break; //moves on after it finds the comment
		}
		
		else {
			CommentTrue = false; //there are no comments
		}
	}
	
	for (unsigned i = 0; i < userCmd.size(); i++) { //traversing to check for a connector
		if (userCmd.at(i) == ';' || userCmd.at(i) == '&' || userCmd.at(i) == '|' || userCmd.at(i) == '(' || userCmd.at(i) == ')') {
			ConnectorTrue = true; //if any connector, flag as true
			break; //moves on after it finds at least one connector
		}
		
		ConnectorTrue = false; //there are no connectors
	}
	
	if (ConnectorTrue == false && CommentTrue == false) { //if only command, then push only command
		combined.push_back(userCmd); //only needs to push a single command
	}
	
	else if (ConnectorTrue == false && CommentTrue == true) { //if just command and comment
		for (unsigned i = 0; i < userCmd.size(); i++) {
			if (userCmd.at(i) == '#') {
				combined.push_back(userCmd.substr(start, i - start)); //pushes everything before comment
			}
		}
	}
	
	else if (ConnectorTrue == true) {
		for (unsigned i = 0; i < userCmd.size(); i++) { //#kimisdumb
			
			if (userCmd.at(i) == ';') { //executes normally because no comment
				combined.push_back(userCmd.substr(start, i - start));
				combined.push_back(";");
				i = i + 1;
				//cout << i << endl;
				start = i + 1;
				//i = i - 1;
				//cout << start << endl;
			}
			
			/*else if (userCmd.at(i) == '(') {
				combined.push_back("("); 
				i = i + 1;
				start = i;
			}*/
			
			else if (userCmd.at(i) == '&') { // checks for And connector
				if (userCmd.at(i + 1) == '&') {
					combined.push_back(userCmd.substr(start, i - 1 - start));
					combined.push_back("&");
					i = i + 2;
					//cout << "this is i: " << i << endl;
					start = i + 1;
					//i = i - 1;
				}
			}
			
			else if (userCmd.at(i) == '|' && userCmd.at(i + 1) == '|') { // checks for Or connector
				//if (userCmd.at(i + 1) == '|') {
					combined.push_back(userCmd.substr(start, i - 1 - start));
					combined.push_back("|");
					i = i + 2;
					start = i + 1;
					//i = i - 1;
				//}
			}
			
			else if (userCmd.at(i) == '(') {
				combined.push_back("(");
				//i = i + 1;
				start = i + 1;
			}
			
			else if (userCmd.at(i) == ')') {
				if (i == (userCmd.size() - 1) && CommentTrue == false) {
					combined.push_back(userCmd.substr(start, i - start));
					combined.push_back(")");
				} 
				
				else {
					if (userCmd.at(i + 1) == ' ') {
						if (userCmd.at(i + 2) == '&' && userCmd.at(i + 3) == '&') {
							combined.push_back(userCmd.substr(start, i - start));
							combined.push_back(")");
							combined.push_back("&");
							i = i + 4;
							start = i + 1;
						}
						
						else if (userCmd.at(i + 2) == '|' && userCmd.at(i + 3) == '|') {
							combined.push_back(userCmd.substr(start, i - start));
							combined.push_back(")");
							combined.push_back("|");
							i = i + 4;
							start = i + 1;
						}
					}
					
					else if (userCmd.at(i + 1) == ';') {
						combined.push_back(userCmd.substr(start, i - start));
						combined.push_back(")");
						combined.push_back(";");
						i = i + 2;
						start = i + 1;
					}
					
					else if (userCmd.at(i + 1) == ')') {
						combined.push_back(userCmd.substr(start, i - start));
						combined.push_back(")");
						combined.push_back(")");
						i = i + 2;
						start = i + 1;
					}
				}
			}
			
			else if (i == (userCmd.size() - 1) && CommentTrue == false) { // if there is no comment 
				//cout << i << endl;
				//cout << start << endl;
				//cout << userCmd.size() << endl;
				combined.push_back(userCmd.substr(start, i - start + 1));
			}
		}
	}
}/**/

int main2() {
	
	bool checkthis = true;
	while(checkthis) {
		cout << "$ "; // reprint console
		string userCmd;
		vector<string> combined;
		getline(cin, userCmd); //gets user input
		
		if (userCmd.find('#') != string::npos) {
			userCmd = userCmd.substr(0, userCmd.find('#'));
		}
		// cout << userCmd << endl;
		while (userCmd.at(userCmd.size() - 1) == ' ') {
			userCmd.pop_back();
		}
		
		parse(userCmd, combined);
		
		for (unsigned i = 0; i < combined.size(); ++i) { //this is just to see everything in combined
			cout << combined.at(i) << endl;
		}
		//shunting_yard(combined)->execute();
	}	
	
	return 0;
}