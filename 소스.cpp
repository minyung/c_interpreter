#include"GetCommands.h"
#include"variable.h"

#pragma once


//선언된 변수들 저장하는 컨테이너
map<string, type> var;

//커맨드 저장 동적 컨테이너, string과 각 커맨드의 level이 저장된다.
vector<COMMAND> command;

//main 함수는 레벨 0, 중괄호 안으로 들어갈 수록 +1
int level = 0;

//각 변수에 주소값을 1부터 차례대로 지정
int pointer = 1;

//라인
int lin=1;

int main(){
	COMMAND tmp;

	command.push_back(tmp);
	while (1){

		cout << lin << " >> ";
		//사용자가 입력하는 한 라인의 커맨드를 읽어오는 함수
		tmp = GetCmd(var, level, pointer, command,0,0,"normal");

		//사용자가 입력한 커맨드가 정상적인 커맨드면 command에 추가
		if (tmp.level != -1)
		{
			command.push_back(tmp);
			command[lin].line = lin;
			lin++;
		}
		printf("level : %d\n", level);
		//PrintState(var);
	}
	return 0;
}