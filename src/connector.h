//This is the connector.h file
#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "base.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class Connector: public Base
{
	public:
		Connector() : Base() {}

		virtual bool execute(int in, int out) = 0; // int a is the input and int b is the out
		virtual bool check() = 0;
};

class Semi:public Connector
{
	/*protected:
		Base* lhs;
		Base* rhs;*/

	public:
		//Semi(Base* lhs, Base* rhs);
		Semi();
		bool execute(int in, int out);
		bool check();
};

class Or : public Connector
{
	/*protected:
		Base* lhs;
		Base* rhs;*/

	public:
		//Or(Base* lhs, Base* rhs);
		Or();
		bool execute(int in, int out);
		bool check();
};

class And : public Connector
{
	/*protected:
		Base* lhs;
		Base* rhs;*/

	public:
		//And(Base* lhs, Base* rhs);
		And();
		bool execute(int in, int out);
		bool check();
};

class Pipe : public Connector
{
	public:
	Pipe();
	bool execute(int in, int out);
	bool check();
};

#endif