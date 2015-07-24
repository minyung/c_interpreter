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
	if (str.find("if") == 0)									//���ۺκ��� if�̰� ��ȣ�� ������ �ʾ��� ��
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)									//(�� �����ϰ� ��ȣ�� ������ �ʾ��� ��
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}											
	else if (str.find("{") == 0)									//��ȣ�� ��������
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//��ȣ�� ������ �ʰ� ������ ��
	{
		printf("��ȣ�� ����� ������ �ʾҽ��ϴ�.\n");
	}

	else if (tack[tackNum].star == false && str!="{")		//��ȣ�� ������ �ʰ� �ٸ� ������ ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//��ȣ�� ������ �ʰ� ;�� ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str!="}")		//��ȣ�� ������ �ٸ� ������ ���� ��
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//��ȣ�� ����� ������ ��
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}
	
	else if (tack[tackNum].fin = true && str.back() == ';')			//��ȣ�� �����µ� �ٸ������� ���� ��
	{
		return -1;
	}
	return 0;
}

int _elseif(string str)
{
	joje tmp;
	int i;

	if (str.find("elseif") == 0)			//elseif ���ۺκ�
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)										//���ǽ�
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (str.find("{") == 0)										//��ȣ�� ��������
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//��ȣ�� ������ �ʰ� ������ ��
	{
		printf("��ȣ�� ����� ������ �ʾҽ��ϴ�.\n");
	}

	else if (tack[tackNum].star == false && str.back() == ';')		//��ȣ�� ������ �ʰ� �ٸ� ������ ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//��ȣ�� ������ �ʰ� ;�� ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		return 0;
	}
	else if (tack[tackNum].star == true && str.back() == ';')		//��ȣ�� ������ �ٸ� ������ ���� ��
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//��ȣ�� ����� ������ ��
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}

	else if (tack[tackNum].fin = true && str.back() == ';')			//��ȣ�� �����µ� �ٸ������� ���� ��
	{
		return -1;
	}
	return 0;
}

int _else(string str)
{
	joje tmp;
	int i;

	if (str.find("else") == 0)											//else ���ۺκ�
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = level;
	}
	else if (str.find("(") == 0)										//���ǽ�
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (str.find("{") == 0)										//��ȣ�� ��������
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)		//��ȣ�� ������ �ʰ� ������ ��
	{
		printf("��ȣ�� ����� ������ �ʾҽ��ϴ�.\n");
	}

	else if (tack[tackNum].star == false && str.back() == ';')		//��ȣ�� ������ �ʰ� �ٸ� ������ ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;
		return 1;
	}
	else if (tack[tackNum].star == false && str.back() == ';')		//��ȣ�� ������ �ʰ� ;�� ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		return 0;
	}
	else if (tack[tackNum].star == true && str.back() == ';')		//��ȣ�� ������ �ٸ� ������ ���� ��
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)										//��ȣ�� ����� ������ ��
	{
		tack[tackNum].fin = true;
		if (tack[tackNum].TnF = true)
			return 1;
		else
			return 0;
	}

	else if (tack[tackNum].fin = true && str.back() == ';')			//��ȣ�� �����µ� �ٸ������� ���� ��
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