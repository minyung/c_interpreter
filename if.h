#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <stack>

#include "getCommands.h"
#include "variable.h"

#pragma once
using namespace std;

struct joje
{
	string type="";//���ǹ��� ����
	string term="";//���ǹ��� ���ǽ�
	string object = "";	//���ǹ��� ����
	int level=0;	//���ǹ��� ��ȣ��ġ
	int jmp=0;	//���ǽ��� �����̶��
	bool star=false;	//���ǹ��� ������ �˸�
	bool fin=false;	//���ǹ��� ���� �˸�
	bool TnF = false;	//���ǽ��� �� ����
};

extern joje tack[20];
extern int tackNum;

bool TnF(string str);
int _if(string str);
COMMAND excu(map<string, type> &var, int &level, int &pointer, const vector<COMMAND> &command, int start, int end, string exc);