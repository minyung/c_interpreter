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



int main(){
	COMMAND tmp;
	while (1){
		//����ڰ� �Է��ϴ� �� ������ Ŀ�ǵ带 �о���� �Լ�
		tmp = GetCmd(var, level, pointer, command);

		//����ڰ� �Է��� Ŀ�ǵ尡 �������� Ŀ�ǵ�� command�� �߰�
		if (tmp.level != -1) command.push_back(tmp);
		PrintState(var);
	}
	return 0;
}