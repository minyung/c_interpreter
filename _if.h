#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <stack>

#include "getCommands.h"
#include "variable.h"
#include "operators.h"


#pragma once
using namespace std;

struct joje
{
	string type="";//���ǹ��� ����
	string first="";	//for�� �ʱ��
	string term="";//���ǹ��� ���ǽ�
	string last=""; //for�� ������
	string object = "";	//���ǹ��� ����
	int paren=0;	//���ǽ��� ��ȣ ����(a==0)
	int level=0;	//���ǹ��� ��ȣ��ġ
	int jmp=0;		//���ǽ��� �����̶��
	int semi = 0;	//for���� �ʱ�, ����, �������� ������ ���� ����(0:�ʱ�,1:����,2:����)
	bool star=false;	//���ǹ��� ������ �˸�
	bool fin=false;	//���ǹ��� ���� �˸�
	bool TnF = false;	//���ǽ��� �� ����
};


extern joje tack[20];
extern int tackNum;
extern int Parenth; //���ǹ��� ��ȣ ����

void pop(int num);

int _if(string str, map<string, type> &var);
int _elseif(string str, map<string, type> &var);
int _else(string str, map<string, type> &var);

int _while(string str, map<string, type> &var);
int _for(string str, map<string, type> &var);
