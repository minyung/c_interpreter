#include"GetCommands.h"
#include"variable.h"

#pragma once


//����� ������ �����ϴ� �����̳�
map<string, type> var;

//Ŀ�ǵ� ���� ���� �����̳�, string�� �� Ŀ�ǵ��� level�� ����ȴ�.
vector<COMMAND> command;

//main �Լ��� ���� 0, �߰�ȣ ������ �� ���� +1
int level = 0;

//�� ������ �ּҰ��� 1���� ���ʴ�� ����
int pointer = 1;

//����
int lin=1;

int main(){
	COMMAND tmp;

	command.push_back(tmp);
	while (1){

		cout << lin << " >> ";
		//����ڰ� �Է��ϴ� �� ������ Ŀ�ǵ带 �о���� �Լ�
		tmp = GetCmd(var, level, pointer, command,0,0,"normal");

		//����ڰ� �Է��� Ŀ�ǵ尡 �������� Ŀ�ǵ�� command�� �߰�
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