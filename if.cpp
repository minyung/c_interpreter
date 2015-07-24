#include <stdio.h>
#include <string.h>
#include <string>
#include <stack>
#include <vector>

#include "if.h"
#include  "GetCommands.h"
#include "operators.h"
#include "variable.h"

#pragma once
using namespace std;

extern int level;
extern int lin;

joje tack[20];
int tackNum = 0;

bool lvchk(int lv)
{
	for (int i = tackNum; i > 0; i--)
	{
		if (level > tack[i].level)
			return 1;
	}
	return 0;
}

int _if(string str)
{
	joje tmp;
	int i;
	if (str.find("if") == 0)									//시작부분이 if이고 괄호가 열리지 않았을 때
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)									//(로 시작하고 괄호가 열리지 않았을 때
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}											
	else if (str.find("{") == 0)									//괄호가 열렸을때
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//괄호가 열리지 않고 닫혔을 때
	{
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str!="{")		//괄호가 열리지 않고 다른 문장이 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str!="}")		//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//괄호가 제대로 닫혔을 때
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}
	
	else if (tack[tackNum].fin = true && str.back() == ';')			//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}

int _elseif(string str)
{
	joje tmp;
	int i;

	if (str.find("elseif") == 0)			//elseif 시작부분
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)										//조건식
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (str.find("{") == 0)										//괄호가 열렸을때
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//괄호가 열리지 않고 닫혔을 때
	{
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str.back() == ';')		//괄호가 열리지 않고 다른 문장이 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		return 0;
	}
	else if (tack[tackNum].star == true && str.back() == ';')		//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//괄호가 제대로 닫혔을 때
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}

	else if (tack[tackNum].fin = true && str.back() == ';')			//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}

int _else(string str)
{
	joje tmp;
	int i;

	if (str.find("else") == 0)											//else 시작부분
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)										//조건식
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (str.find("{") == 0)										//괄호가 열렸을때
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//괄호가 열리지 않고 닫혔을 때
	{
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str.back() == ';')		//괄호가 열리지 않고 다른 문장이 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		return 0;
	}
	else if (tack[tackNum].star == true && str.back() == ';')		//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//괄호가 제대로 닫혔을 때
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}

	else if (tack[tackNum].fin = true && str.back() == ';')			//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}
COMMAND excu(map<string, type> &var, int &level, int &pointer, const vector<COMMAND> &command, int start, int end)
{
	GetCmd(var, level, pointer, command, 1, 2, "normal");
	COMMAND ret = COMMAND("sss", level);
	return ret;
}