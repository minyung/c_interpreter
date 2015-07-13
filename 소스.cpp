#include<cstdio>
#include<cstring>
#include"variable.h"
#include<iostream>
#include<queue>

//선언된 변수들 저장하는 컨테이너
map<string, type> var;
map<string, type>::iterator it;



//main 함수는 레벨 0, 중괄호 안으로 들어갈 수록 +1
int level = 0;

//각 변수에 주소값을 1부터 차례대로 지정
int pointer = 1;

int main(){
	char command[120];
	while (gets(command)){
		if (command[strlen(command) - 1] != ';'){
			puts("세미콜론(;)으로 끝나지 않습니다!");
			continue;
		}
		//커맨드를 쉼표 단위로 나누어 큐에 저장
		queue<string> qCmd;

		string token;
		for (int here = 0; command[here]; here++){
			//연산자면 토큰읂 끊고 연산자도 큐에 넣는다
			if (command[here] == '=' || command[here] == '+'){
				qCmd.push(token);
				token.clear();
				
				token += command[here];
				qCmd.push(token);
				token.clear();
			}
			//띄어쓰기면 그냥 넘어간다
			else if (command[here] == ' '){
				if (token != "") qCmd.push(token);
				token.clear();
				continue;
			}
			//쉼표나 세미콜론이면 토큰을 끊는다
			else if (command[here] == ',' || command[here] == ';'){
				qCmd.push(token);
				token.clear();
			}
			//나머지는 토큰에 이어붙인다
			else{
				token += command[here];
			}
		}
		token.clear();
		string oldtoken;
		//나누어진 토큰의 첫 부분(if, int, while 등)에 따라 호출되는 함수가 다르게끔 설정
		while (qCmd.size()){
			token = qCmd.front();
			//토큰의 첫 부분이 변수의 자료형이면 뒷 부분은 반드시 변수의 이름이 나온다
			/*변수 타입 구분
			1 == int
			2 == char
			3 == double
			*/
			if (token == "int"){
				oldtoken = token;
			}
			else if (token == "char"){
				oldtoken = token;
			}
			else if (token == "double"){
				oldtoken = token;
			}
			else if (token == "if"){
			}
			else if (token == "for"){
			}
			// 토큰이 변수 선언, if, for, while, 연산도 아니면 변수 이름인 것이다
			else{
				if (oldtoken == "int"){
					if (var[token].pnt == 0)
						var[token] = type(1, (int)0, level, pointer++);
				}
				else if (oldtoken == "char"){
					if (var[token].pnt == 0)
						var[token] = type(2, (char)0, level, pointer++);
				}
				else if (oldtoken == "double"){
					if (var[token].pnt == 0)
						var[token] = type(3, (double)0, level, pointer++);
				}
			}
			qCmd.pop();
		}
		
		

		//한 줄 처리가 끝나면 현재의 상황을 출력
		puts("//-----------------//");
		puts("현재 변수 목록");
		for (it = var.begin(); it != var.end(); it++){
			if (it->second.datatype == 1)
				cout << "int " << it->first << " = " << it->second.u.value_int << " 주소 : " << it->second.pnt << endl;
			if (it->second.datatype == 2)
				cout << "char " << it->first << " = " << it->second.u.value_char << " 주소 : " << it->second.pnt << endl;
			if (it->second.datatype == 3)
				cout << "double " << it->first << " = " << it->second.u.value_double << " 주소 : " << it->second.pnt << endl;
		}
	}
	return 0;
}