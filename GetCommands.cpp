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
		//띄어쓰기면 그냥 넘어간다
		if (TMPcmd[here] == ' '){
			continue;
		}
		//쉼표나 세미콜론이면 토큰을 끊는다
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
		//나머지는 토큰에 이어붙인다
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
		//연산자면 토큰을 끊고 연산자도 큐에 넣는다
		/* ===============================
			연산자 토큰 분리 - 2015.07.18 심민영 start
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
		     연산자 토큰 분리 - 2015.07.18 심민영 end
		   ===============================*/
		//띄어쓰기면 그냥 넘어간다
		else if (TMPcmd[here] == ' '){
			if (token != "") vToken.push_back(token);
			token.clear();
			continue;
		}
		//쉼표나 세미콜론이면 토큰을 끊는다
		else if (TMPcmd[here] == ',' || TMPcmd[here] == ';'){
			vToken.push_back(token);
			vToken.push_back(";");
			token.clear();
		}
		else if (TMPcmd[here] == '{'){
			vToken.push_back(token);
			vToken.push_back("{");
			token.clear();
		}
		else if (TMPcmd[here] == '}'){
			vToken.push_back(token);
			vToken.push_back("}");
			token.clear();
		}
		//나머지는 토큰에 이어붙인다
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
	if (start == 0 && exc.compare("normal")==0)
	{
		gets(buf);
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

	//if가 끝난뒤에 일반문장이 나오면  스택 팝
	if (tack[tackNum].fin == true && TMPcmd.find("else if") != 0 && TMPcmd.find("else") != 0 && exc.compare("normal")==0)
	{
		joje tmp;
		tack[tackNum] = tmp;
		tackNum--;
	}

	for (; k <= cou; k++)
	{
		vector<string> vToken;
		if (TMPcmd == "")
			break;

		if (TMPcmd.find("if") == 0 || (tack[tackNum].fin == false && tackNum>0))
		{
			vToken = CreateJojeToken(TMPcmd);
		}
		else if (TMPcmd.find("else if") == 0 || (tack[tackNum].fin == false && tackNum > 0))
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
				puts("세미콜론(;)으로 끝나지 않습니다!");
				ret.level = -1;
				return ret;
			}

			vToken = CreateToken(TMPcmd);
		}
		

		//커맨드를 쉼표 단위로 나누어 벡터에 저장

		string token, oldtoken;
		//나누어진 토큰의 첫 부분(if, int, while 등)에 따라 호출되는 함수가 다르게끔 설정

	/*	for (int i = 0; i < vToken.size(); i++){
			cout << vToken[i].c_str() << " ";
		}*/

		for (int i = 0; i < vToken.size(); i++)
		{
			token = vToken[i];

			//토큰의 첫 부분이 변수의 자료형이면 뒷 부분은 반드시 변수의 이름이 나온다
			/*변수 타입 구분
			1 == int
			2 == char
			3 == double
			*/
			/* ===============================
				연산자 토큰 처리 - 2015.07.18 심민영 start
				===============================*/
			int prec = PrecOper().GetPrecedence(token);

			if (token == ";" && (tackNum == 0 && TMPcmd.find("if")!=0)){
				continue;
			}
			/* ===============================
			연산자 토큰 처리 - 2015.07.18 심민영 end
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
			else if (token == "if" || (tackNum>0 && tack[tackNum].fin == false)){
				if (_if(token,var) == 1)
				{
					if (tackNum == 1)
					{
						GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
					}
					level--;
				}

			}

			//else if (token == "elseif" || (tackNum>0 && tack[tackNum].fin == false)){
			//	//_if(var,  level,  pointer, command, start, end);
			//	if (_if(token,var) == 1)
			//	{
			//		if (tackNum == 1)
			//		{
			//			GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
			//		}
			//	}
			//}
			//else if (token == "else" || (tackNum>0 && tack[tackNum].fin == false)){
			//	//_if(var,  level,  pointer, command, start, end);
			//	if (_if(token,var) == 1)
			//	{
			//		if (tackNum == 1)
			//		{
			//			GetCmd(var, level, pointer, command, start, end, tack[tackNum].object);
			//		}
			//	}
			//}
			else if (token == "for"){
			}
			/* ===============================
				연산자 토큰 처리 - 2015.07.18 심민영 start
				===============================*/
			else if (prec != -1){
				PrecOper().infix_to_postfix(vToken, &i, var);
			}
			/* ===============================
				연산자 토큰 처리 - 2015.07.18 심민영 end
				===============================*/
			// 토큰이 변수 선언, if, for, while, 연산도 아니면 변수 이름인 것이다
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
					printf("괄호가 열리지 않았습니다.\n");
				else if (tackNum == 0)
					level--;
			}
		}
	}

	ret = COMMAND(TMPcmd, level);
	return ret;
}