#include"GetCommands.h"
#include "variable.h"
#include"operators.h"
#include "_if.h"


#pragma once
vector<string> CreateJojeToken(string TMPcmd){
	vector<string> vToken;
	string token;
	int count = -1000;
	for (int here = 0; here < TMPcmd.length(); here++){
		//����� �׳� �Ѿ��
		if (TMPcmd[here] == ' '){
			continue;
		}
		//��ǥ�� �����ݷ��̸� ��ū�� ���´�
		else if (TMPcmd[here] == ';'){
			vToken.push_back(token + ";");
			token.clear();
		}
		else if (TMPcmd[here] == '{'){
			if (token == "")
			{
				vToken.push_back("{");
			}
			else
			{
				vToken.push_back(token);
				vToken.push_back("{");
			}
			
			token.clear();
		}
		else if (TMPcmd[here] == '}'){
			if (token == "")
			{
				vToken.push_back("}");
			}
			else
			{
				vToken.push_back(token);
				vToken.push_back("}");
			}
			token.clear();
		}
		else if (count == -1000 && TMPcmd[here] == '(')
		{
			if (token == "")
			{
			}
			else
				vToken.push_back(token);
			token.clear();
			token = "(";
			count = 1;
		}
		else if (TMPcmd[here] == '(')
		{
			count++;
		}
		else if (count == 1 && TMPcmd[here] == ')')
		{
			vToken.push_back(token+")");
			token.clear();
		}
		else if (TMPcmd[here] == ')')
		{
			count--;
		}
		//�������� ��ū�� �̾���δ�
		else{
			token += TMPcmd[here];
		}
	}
	return vToken;
}

vector<string> CreateToken(string TMPcmd){
	
	vector<string> vToken;
	string token;
	for (int here = 0; here < TMPcmd.length(); here++){
		//�����ڸ� ��ū�� ���� �����ڵ� ť�� �ִ´�
		/* ===============================
			������ ��ū �и� - 2015.07.18 �ɹο� start
		   ===============================*/
		string sOper;
		if (isOper(TMPcmd, &here, &sOper)){
			if (token != ""){
				vToken.push_back(token);
				token.clear();
			}
	//		cout << sOper << endl;

			token += sOper;
			vToken.push_back(token);
			token.clear();
		}
		/* ===============================
		     ������ ��ū �и� - 2015.07.18 �ɹο� end
		   ===============================*/
		//����� �׳� �Ѿ��
		else if (TMPcmd[here] == ' '){
			if (token != "") vToken.push_back(token);
			token.clear();
			continue;
		}
		//��ǥ�� �����ݷ��̸� ��ū�� ���´�
		else if (TMPcmd[here] == ',' || TMPcmd[here] == ';'){
			if (token == "")
			{
			}
			else
				vToken.push_back(token);
			vToken.push_back(";");
			token.clear();
		}
		else if (TMPcmd[here] == '{'){
			if (token == "")
			{
			}
			else
				vToken.push_back(token);
			vToken.push_back("{");
			token.clear();
		}
		else if (TMPcmd[here] == '}'){
			if (token == "")
			{
			}
			else
				vToken.push_back(token);
			vToken.push_back("}");
			token.clear();
		}
		//�������� ��ū�� �̾���δ�
		else{
			token += TMPcmd[here];
		}
	}
	return vToken;
}

COMMAND GetCmd(map<string, type> &var, int &level, int &pointer, const vector<COMMAND> &command, int start, int end, string exc){
	COMMAND ret;
	char buf[120];
	string TMPcmd;
	int cou, k;
	if (start == 0 && exc.compare("normal") == 0)
	{
		gets_s(buf);
		TMPcmd = buf;
		k = 0;
		cou = 0;
	}
	else if (start > 0)
	{
		TMPcmd = command[start].cmd;
		cou = end - start;
		k = start;
		cou = end - start + 1;
	}
	else
	{
		TMPcmd = exc;
		k = 0;
		cou = 0;
	}

	//if�� �����ڿ� �Ϲݹ����� ������ ��� ���� ����
	if (tack[tackNum].fin == true && TMPcmd.find("else if") != 0 && TMPcmd.find("else") != 0 && exc.compare("normal")==0)
	{
		for (int i = 1; i <= tackNum; i++)
		{
			joje tmp;
			tack[i] = tmp;
			tackNum = 0;
		}
	}

	for (; k <= cou; k++)
	{
		vector<string> vToken;
		if (TMPcmd == "")
			break;
		/*
		if (TMPcmd.find("if") != -1)
		{
		vToken = CreateJojeToken(TMPcmd);
		}
		else if (TMPcmd.find("else if") != -1)
		{
		vToken = CreateJojeToken(TMPcmd);
		}
		else if (TMPcmd.find("else") == 0 || (tack[tackNum].fin == false && tackNum > 0))
		{
		vToken = CreateJojeToken(TMPcmd);
		}
		else
		{
		if (TMPcmd.back() != ';' && TMPcmd.back() != '{' && TMPcmd.back() != '}'){
		puts("�����ݷ�(;)���� ������ �ʽ��ϴ�!");
		ret.level = -1;
		return ret;
		}

		*/
		
		vToken = CreateToken(TMPcmd);

		
		//Ŀ�ǵ带 ��ǥ ������ ������ ���Ϳ� ����
		string token, oldtoken;
		//�������� ��ū�� ù �κ�(if, int, while ��)�� ���� ȣ��Ǵ� �Լ��� �ٸ��Բ� ����

	/*	for (int i = 0; i < vToken.size(); i++){
			cout << vToken[i].c_str() << " ";
		}*/

		//else  �� ġ�� ��ū���� �νĵ��� �ʴ� ���� �ذ�..
		if (TMPcmd == "else")
			vToken.push_back("else");
		for (int i = 0; i < vToken.size(); i++)
		{
			token = vToken[i];

			//��ū�� ù �κ��� ������ �ڷ����̸� �� �κ��� �ݵ�� ������ �̸��� ���´�
			/*���� Ÿ�� ����
			1 == int
			2 == char
			3 == double
			*/
			/* ===============================
				������ ��ū ó�� - 2015.07.18 �ɹο� start
				===============================*/
			int prec = PrecOper().GetPrecedence(token);

			if (token == ";" && (tackNum == 0 && TMPcmd.find("if")!=0)){
				continue;
			}
			/* ===============================
			������ ��ū ó�� - 2015.07.18 �ɹο� end
			===============================*/
			if (token == "int"){
				oldtoken = token;
			}
			else if (token == "char"){
				oldtoken = token;
			}
			else if (token == "double"){
				oldtoken = token;
			}
			//��� if ó��
			else if (token == "if" || (tackNum>0 && tack[tackNum].type == "if" && tack[tackNum].fin == false))
			{
				if (_if(token,var) == 1)
				{
					GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
					level--;
				}

			}
			//else �� else if, else if���� ���� ó��
			else if (token == "else" || token == "elseif" || (tackNum > 0 && tack[tackNum].type == "elif" && tack[tackNum].fin == false))
			{
				if (token == "else")
				{
					if (vToken.size() > 1 && vToken[i + 1] == "if")
					{
						i++;
						int rt = _elseif(token, var);
						if (rt == 1)
						{
							GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
							level--;
						}
						else if (rt == -1)
							return ret;
					}
					else
					{
						int rt = _else(token, var);
						if (rt == 1)
						{
							GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
							level--;
						}
						else if (rt == -1)
							return ret;
					}
				}
				else if (token == "elseif" || (tackNum > 0 && tack[tackNum].type == "elif" && tack[tackNum].fin == false))
				{
					if (_elseif(token, var) == 1)
					{
						GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
						level--;
					}
				}
				
			}
			//else if���� ����ó��
			else if ((tackNum > 0 && tack[tackNum].type == "else" && tack[tackNum].fin == false))
			{
				int rt = _else(token, var);
				if (rt == 1)
				{
					GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
					level--;
				}
				else if (rt == -1)
					return ret;
			}
			//while
			else if (token == "while" || (tackNum>0 && tack[tackNum].type == "while" && tack[tackNum].fin == false))
			{
				while(_while(token, var) == 1)
				{
					GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
					while (tack[tackNum].type != "while")
						pop(1);
					level--;
				}
				if (tack[tackNum].fin == true)
				{
					//level--;
					pop(1);
				}
			}
			//for
			else if (token == "for" || (tackNum>0 && tack[tackNum].type == "for" && tack[tackNum].fin == false))
			{
				while (_for(token, var) == 1)
				{
					GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
					while (tack[tackNum].type != "for")
						pop(1);
					GetCmd(var, level, pointer, command, start, end, tack[tackNum].last);
					level--;
				}
				if (tack[tackNum].fin == true)
				{
					//level--;
					pop(1);
				}
			}
			else if (token == "for"){
			}
			/* ===============================
				������ ��ū ó�� - 2015.07.18 �ɹο� start
				===============================*/
			else if (prec != -1){
				PrecOper().infix_to_postfix(vToken, &i, var);
				i--;
			}
			/* ===============================
				������ ��ū ó�� - 2015.07.18 �ɹο� end
				===============================*/
			// ��ū�� ���� ����, if, for, while, ���굵 �ƴϸ� ���� �̸��� ���̴�
			else{
				if (oldtoken == "int"){
					if (var[token].pnt == 0 && isValidName(token))
						var[token] = type(1, (int)0, level, pointer++);
				}
				else if (oldtoken == "char" && isValidName(token)){
					if (var[token].pnt == 0)
						var[token] = type(2, (char)0, level, pointer++);
				}
				else if (oldtoken == "double" && isValidName(token)){
					if (var[token].pnt == 0)
						var[token] = type(3, (double)0, level, pointer++);
				}
			}

			if (end-start > 0)
				TMPcmd = command[start + i].cmd;

			if (token == "{" && tackNum == 0) level++;
			else if (token == "}")
			{
				if (level == 0 && tackNum == 0)
				{
				}
				else if (tackNum == 0)
					level--;
			}
		}
	}

	ret = COMMAND(TMPcmd, level);
	return ret;
}