//this is the base.h file
#ifndef BASE_H
#define BASE_H

#include <string>
using namespace std;

class Base{
public:
    Base *lhs;
    Base *rhs;
	Base() {} 
	void set(Base *lhs, Base *rhs) {
	    this->lhs = lhs;
	    this->rhs = rhs;
	}
	virtual bool check() = 0;
	virtual bool execute(int in, int out) = 0;
	// virtual string get_data() = 0;
	// virtual void print() = 0;

};
#endif