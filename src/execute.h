#ifndef EXECUTE_H
#define EXECUTE_H
#include <vector>
#include <iostream>
#include "base.h"

using namespace std;

class Execute: public Base {
	protected:
		vector<string> exeString;
		string input;
		string output;

	public:
		Execute() : Base() {}
		Execute(string someString);
		Execute(vector<string>);
		bool execute(int in, int out);
		bool check();
		bool system_calling(vector<char*> cmdSystem);
};

#endif
