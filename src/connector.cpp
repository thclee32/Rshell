//This is the connector.h
#include "connector.h"
#include "base.h"
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

/*Semi::Semi(Base* lhs, Base* rhs) : Connector()
{
	this->lhs = lhs;
	this->rhs = rhs;
}*/

Semi::Semi() : Connector() {}

bool Semi::execute(int in, int out) {
	lhs->execute(0, 1);
	bool a = rhs->execute(0, 1);
	if(a) {
		return true;
	}
	return false;
}

bool Semi::check() {
	return false;
}

// void Semi::print() {
// 	cout << ";" << endl;
// }

/*Or::Or(Base* lhs, Base* rhs) : Connector()
{
	this->lhs = lhs;
	this->rhs = rhs;
}*/
Or::Or() : Connector() {}

bool Or::execute(int in, int out) {
	if(lhs->execute(0, 1)) {
		return true;
	}

	else {
		if(rhs->execute(0, 1)) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Or::check() {
	return false;
}

// void Or::print() {
// 	cout << "||" << endl;
// }

/*And::And(Base* lhs, Base* rhs) : Connector()
{
	this->lhs = lhs;
	this->rhs = rhs;
}*/
And::And() : Connector() {}

bool And::execute(int in, int out) {
	if(lhs->execute(0, 1)) {
		if(rhs->execute(0, 1)) {
			return true;
		}
		
		else {
			return false;
		}
	}
	
	return false;
}

bool And::check() {
	return false;
}

Pipe::Pipe() : Connector() {}

bool Pipe::execute(int in, int out) {
	int fds[2];
	pipe(fds);
	
	lhs->execute(in, fds[1]);
	rhs->execute(fds[0], out);
	
	close(fds[0]);
	close(fds[1]);
	
	return true; //???????
	
}

bool Pipe::check()
{
	return false;
}

// void And::print() {
// 	cout << "&&" << endl;
// }