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
	string first="";	//for의 초기식
	string term="";//조건문의 조건식
	string last=""; //for의 증감식
	string object = "";	//조건문의 내용
	int paren=0;	//조건식의 괄호 갯수(a==0)
	int level=0;	//조건문의 괄호위치
	int jmp=0;		//조건식이 거짓이라면
	int semi = 0;	//for에서 초기, 조건, 증감식을 나누기 위한 변수(0:초기,1:조건,2:증감)
	bool star=false;	//조건문의 시작을 알림
	bool fin=false;	//조건문의 끝을 알림
	bool TnF = false;	//조건식의 참 거짓
};


extern joje tack[20];
extern int tackNum;
extern int Parenth; //조건문의 괄호 갯수

void pop(int num);

int _if(string str, map<string, type> &var);
int _elseif(string str, map<string, type> &var);
int _else(string str, map<string, type> &var);

int _while(string str, map<string, type> &var);
int _for(string str, map<string, type> &var);
