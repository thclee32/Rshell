//This is rshell.h Where the parsing will be done
#ifndef RSHELL_H
#define RSHELL_H
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include "command.h"
#include "connector.h"
#include "base.h"
#include "execute.h"
#include <stack>
#include <queue>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

using namespace std;

queue<string> shunting_yard(vector<vector<char*> > cmdVector);
void removeSemi(vector<char*> &someVector);
void removeLeft(vector<char*> &leeVector);
void removeRight(vector<char*> &reeVector);
int main2();

#endif