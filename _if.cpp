#include "_if.h"

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

void pop(int num)
{
	joje tmp;
	for (int i = num; i > 0; i--)
	{
		tack[tackNum] = tmp;
		tackNum--;
	}
}

int _if(string str, map<string, type> &var)
{
	joje tmp;
	int ind = 0;
	vector<string> operTokens;

	if (str.find("if") == 0)					//���ۺκ��� if�� ��
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = ++level;
	}
	else if (str.find("(") == 0 )				//'('�� ������ ��
	{
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (str.find("{") == 0)								//��ȣ�� ��������
	{
		tack[tackNum].star = true;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)	//��ȣ�� ������ �ʰ� ������ ��
	{
		for (int i = tackNum; i > 0; i--)
		{
			if (tack[i].fin == true)
				pop(1);
			else
			{

			}
		}
		printf("��ȣ�� ����� ������ �ʾҽ��ϴ�.\n");
	}

	else if (tack[tackNum].star == false && str != "{")			//��ȣ�� ������ �ʰ� �ٸ� ������ ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
		tack[tackNum].object += str;

		operTokens = CreateToken(tack[tackNum].term + ";");
		tack[tackNum].TnF = PrecOper().infix_to_postfix(operTokens, &ind, var);

		if (tack[tackNum].TnF)
			return 1;
		else
		{
			level--;
			return 0;
		}
	}
	else if (tack[tackNum].star == false && str.back() == ';')	//��ȣ�� ������ �ʰ� ;�� ���� ��
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str != "}")			//��ȣ�� ������ �ٸ� ������ ���� ��
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)								//��ȣ�� ����� ������ ��
	{
		tack[tackNum].fin = true;
		operTokens = CreateToken(tack[tackNum].term + ";");
		tack[tackNum].TnF = PrecOper().infix_to_postfix(operTokens, &ind, var);

		if (tack[tackNum].TnF)
			return 1;
		else
		{
			level--;
			return 0;
		}
	}

	else if (tack[tackNum].fin = true && str.back() == ';')		//��ȣ�� �����µ� �ٸ������� ���� ��
	{
		return -1;
	}
	return 0;
}
















int _elseif(string str)
{
	joje tmp;

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