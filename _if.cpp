#include "_if.h"

#pragma once
using namespace std;

extern int level;
extern int lin;

joje tack[20];
int tackNum = 0;
int Parenth = 0;
bool lvchk()
{
	int i;
	for (i = tackNum; i > 0; i--)
	{
		if (level+1 != tack[i].level)	//if안에 lv은 항상 밖의 레벨보다 1크다. (엘스이프 구분하기위해 사용)
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


	if (!str.find("}") && Parenth == 1)
	{
		Parenth--;
	}
	else if (tack[tackNum].star == true && tack[tackNum].fin == false)
	{
		if (!str.find("{"))
		{
			Parenth++;
		}
		if (!str.find("}"))
		{
			Parenth--;
		}
		tack[tackNum].object += str;
		return 0;
	}


	if (str.find("if") == 0)					//시작부분이 if일 때
	{
		tmp.type = str;
		tack[++tackNum] = tmp;
		tack[tackNum].level = ++level;
	}
	else if (tack[tackNum].star == false && str.find('(')==0 && tack[tackNum].paren==0)		//'{'가 시작하기 전 맨처음 '('
	{
		tack[tackNum].paren = 1;
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (tack[tackNum].star == false && tack[tackNum].paren > 0)	//'('가 온 다음부터 문자열
	{
		if (str.find('(') == 0)
			tack[tackNum].paren++;
		if (str.find(')') == 0)
			tack[tackNum].paren--;
		tmp.term += str;
		tack[tackNum].term += str;
	}
	else if (str.find("{") == 0)	//괄호가 열렸을때
	{
		tack[tackNum].star = true;
		Parenth++;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)	//괄호가 열리지 않고 닫혔을 때
	{
		for (int i = tackNum; i > 0; i--)
		{
			if (tack[i].fin == true)
				pop(1);
			else
			{

			}
		}
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str != "{")			//괄호가 열리지 않고 다른 문장이 왔을 때
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
	else if (tack[tackNum].star == false && str.back() == ';')	//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str != "}")			//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)								//괄호가 제대로 닫혔을 때
	{
		int i0;
		tack[tackNum].fin = true;

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

	else if (tack[tackNum].fin = true && str.back() == ';')		//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}

int _elseif(string str, map<string, type> &var)
{
	joje tmp;
	int ind = 0;
	vector<string> operTokens;


	if (!str.find("}") && Parenth == 1)
	{
		Parenth--;
	}
	else if (tack[tackNum].star == true && tack[tackNum].fin == false)
	{
		if (!str.find("{"))
		{
			Parenth++;
		}
		if (!str.find("}"))
		{
			Parenth--;
		}
		tack[tackNum].object += str;
		return 0;
	}

	if (str.find("else") == 0 || str.find("elseif") == 0)					//시작부분이 else if일 때
	{
		for (int i0 = tackNum; i0 > 0; i0--)	//레벨이 다른 if문들 전부 팝
		{
			while (lvchk())
			{
				pop(tackNum);
			}
		}

		if (tack[1].type == "")
		{
			printf("if를 선언하세요\n");
			return -1;
		}
		
		tmp.type = "elif";
		tack[++tackNum] = tmp;
		tack[tackNum].level = ++level;

		
	}
	else if (str.find("if") == 0)
	{}
	else if (tack[tackNum].star == false && str.find('(') == 0 && tack[tackNum].paren == 0)		//'{'가 시작하기 전 맨처음 '('
	{
		tack[tackNum].paren = 1;
		tmp.term = str;
		tack[tackNum].term = str;
	}
	else if (tack[tackNum].star == false && tack[tackNum].paren > 0)	//'('가 온 다음부터 문자열
	{
		if (str.find('(') == 0)
			tack[tackNum].paren++;
		if (str.find(')') == 0)
			tack[tackNum].paren--;
		tmp.term += str;
		tack[tackNum].term += str;
	}
	else if (str.find("{") == 0)								//괄호가 열렸을때
	{
		tack[tackNum].star = true;
		Parenth++;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)	//괄호가 열리지 않고 닫혔을 때
	{
		for (int i = tackNum; i > 0; i--)
		{
			if (tack[i].fin == true)
				pop(1);
			else
			{

			}
		}
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str != "{")			//괄호가 열리지 않고 다른 문장이 왔을 때
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
	else if (tack[tackNum].star == false && str.back() == ';')	//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str != "}")			//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)								//괄호가 제대로 닫혔을 때
	{
		int i0;
		tack[tackNum].fin = true;

		tack[tackNum].fin = true;
		operTokens = CreateToken(tack[tackNum].term + ";");
		tack[tackNum].TnF = PrecOper().infix_to_postfix(operTokens, &ind, var);

		int ck;
		for (ck = tackNum; ck > 0; ck--)
		{
			if (tack[ck].type == "if")
				break;
		}

		for (; ck < tackNum; ck++)
		{
			if (tack[ck].TnF == true)
			{
				level--;
				return 0;
			}
		}

		if (tack[tackNum].TnF)
			return 1;
		else
		{
			level--;
			return 0;
		}
	}

	else if (tack[tackNum].fin = true && str.back() == ';')		//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}

int _else(string str, map<string, type> &var)
{
	joje tmp;
	int ind = 0;
	vector<string> operTokens;


	if (!str.find("}") && Parenth == 1)
	{
		Parenth--;
	}
	else if (tack[tackNum].star == true && tack[tackNum].fin == false)
	{
		if (!str.find("{"))
		{
			Parenth++;
		}
		if (!str.find("}"))
		{
			Parenth--;
		}
		tack[tackNum].object += str;
		return 0;
	}

	if (str.find("else") == 0)					//시작부분이 else 일 때
	{
		for (int i0 = tackNum; i0 > 0; i0--)	//레벨이 다른 if문들 전부 팝
		{
			while (lvchk())
			{
				pop(tackNum);
			}
		}

		if (tack[1].type == "")
		{
			printf("if를 선언하세요\n");
			return -1;
		}

		tmp.type = "else";
		tack[++tackNum] = tmp;
		tack[tackNum].level = ++level;


	}
	else if (str.find("{") == 0)								//괄호가 열렸을때
	{
		tack[tackNum].star = true;
		Parenth++;
	}
	else if (tack[tackNum].star == false && str.find("}") == 0)	//괄호가 열리지 않고 닫혔을 때
	{
		for (int i = tackNum; i > 0; i--)
		{
			if (tack[i].fin == true)
				pop(1);
			else
			{

			}
		}
		printf("괄호가 제대로 열리지 않았습니다.\n");
	}

	else if (tack[tackNum].star == false && str != "{")			//괄호가 열리지 않고 다른 문장이 왔을 때
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
	else if (tack[tackNum].star == false && str.back() == ';')	//괄호가 열리지 않고 ;만 왔을 때
	{
		tack[tackNum].star = true;
		tack[tackNum].fin = true;
		tack[tackNum].jmp = lin + 1;
	}
	else if (tack[tackNum].star == true && str != "}")			//괄호가 열리고 다른 문장이 왔을 때
	{
		tack[tackNum].object += str;
	}
	else if (str.find("}") == 0)								//괄호가 제대로 닫혔을 때
	{
		int i0;
		tack[tackNum].fin = true;

		int ck;
		for (ck = tackNum; ck > 0; ck--)
		{
			if (tack[ck].type == "if")
				break;
		}

		for (; ck < tackNum; ck++)
		{
			if (tack[ck].TnF == true)
			{
				level--;
				return 0;
			}
		}
		return 1;
	}

	else if (tack[tackNum].fin = true && str.back() == ';')		//괄호가 닫혔는데 다른문장이 왔을 때
	{
		return -1;
	}
	return 0;
}
