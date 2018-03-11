//This is the connector.h
#include "connector.h"
#include "base.h"
#include <iostream>

using namespace std;

/*Semi::Semi(Base* lhs, Base* rhs) : Connector()
{
	this->lhs = lhs;
	this->rhs = rhs;
}*/

Semi::Semi() : Connector() {}

bool Semi::execute() {
	lhs->execute();
	bool a = rhs->execute();
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

bool Or::execute() {
	if(lhs->execute()) {
		return true;
	}

	else {
		if(rhs->execute()) {
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

bool And::execute() {
	if(lhs->execute()) {
		if(rhs->execute()) {
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

// void And::print() {
// 	cout << "&&" << endl;
// }