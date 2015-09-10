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
	string type="";//조건문의 종류
	string term="";//조건문의 조건식
	string object = "";	//조건문의 내용
	int paren=0;	//조건식의 괄호 갯수(a==0)
	int level=0;	//조건문의 괄호위치
	int jmp=0;	//조건식이 거짓이라면
	bool star=false;	//조건문의 시작을 알림
	bool fin=false;	//조건문의 끝을 알림
	bool TnF = false;	//조건식의 참 거짓
};


extern joje tack[20];
extern int tackNum;
extern int Parenth; //조건문의 괄호 갯수

int _if(string str, map<string, type> &var);
int _elseif(string str, map<string, type> &var);
int _else(string str, map<string, type> &var);
