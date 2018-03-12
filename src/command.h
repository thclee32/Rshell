//This is the command.h ile
#ifndef COMMAND_H
#define COMMAND_H
#include "base.h"
#include <vector>

using namespace std;

class Command: public Base
{
protected:
	vector<char*> args();
public:
	Command() : Base() {}
	//Command(vector<char*> arg);
	bool execute();
};


#endif