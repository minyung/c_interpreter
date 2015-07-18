#include<string>
#include<map>
#include<vector>
#include"variable.h"

#pragma once

using namespace std;

struct COMMAND{
	string cmd;
	int level;
	COMMAND(){}
	COMMAND(string cmd, int level)
		:cmd(cmd), level(level){}
};

vector<string> CreateToken(string TMPcmd);

COMMAND GetCmd(map<string, type> &var, int &level, int &pointer, const vector<COMMAND> &command);

