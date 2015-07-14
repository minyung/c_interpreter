#include<cstdio>
#include<cstring>
#include"variable.h"
#include<iostream>
#include<queue>
#include<vector>

//����� ������ �����ϴ� �����̳�
map<string, type> var;
map<string, type>::iterator it;

//Ŀ�ǵ� ���� ���� �����̳�
vector<string> command;

//main �Լ��� ���� 0, �߰�ȣ ������ �� ���� +1
int level = 0;

//�� ������ �ּҰ��� 1���� ���ʴ�� ����
int pointer = 1;

int main(){
	char buf[120];
	string cmd;
	while (gets(buf)){
		command.push_back(buf);
		cmd = command.back();
		if (cmd.back() != ';'){
			puts("�����ݷ�(;)���� ������ �ʽ��ϴ�!");
			command.pop_back();
			continue;
		}
		//Ŀ�ǵ带 ��ǥ ������ ������ ť�� ����
		queue<string> qCmd;

		string token;
		for (int here = 0; here < cmd.length(); here++){
			//�����ڸ� ��ū�� ���� �����ڵ� ť�� �ִ´�
			if (cmd[here] == '=' || cmd[here] == '+'){
				qCmd.push(token);
				token.clear();

				token += command[here];
				qCmd.push(token);
				token.clear();
			}
			//����� �׳� �Ѿ��
			else if (cmd[here] == ' '){
				if (token != "") qCmd.push(token);
				token.clear();
				continue;
			}
			//��ǥ�� �����ݷ��̸� ��ū�� ���´�
			else if (cmd[here] == ',' || cmd[here] == ';'){
				qCmd.push(token);
				token.clear();
			}
			//�������� ��ū�� �̾���δ�
			else{
				token += cmd[here];
			}
		}
		token.clear();
		string oldtoken;
		//�������� ��ū�� ù �κ�(if, int, while ��)�� ���� ȣ��Ǵ� �Լ��� �ٸ��Բ� ����
		while (qCmd.size()){
			token = qCmd.front();
			//��ū�� ù �κ��� ������ �ڷ����̸� �� �κ��� �ݵ�� ������ �̸��� ���´�
			/*���� Ÿ�� ����
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
			// ��ū�� ���� ����, if, for, while, ���굵 �ƴϸ� ���� �̸��� ���̴�
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



		//�� �� ó���� ������ ������ ��Ȳ�� ���
		puts("//-----------------//");
		puts("���� ���� ���");
		for (it = var.begin(); it != var.end(); it++){
			if (it->second.datatype == 1)
				cout << "int " << it->first << " = " << it->second.u.value_int << " �ּ� : " << it->second.pnt << endl;
			if (it->second.datatype == 2)
				cout << "char " << it->first << " = " << it->second.u.value_char << " �ּ� : " << it->second.pnt << endl;
			if (it->second.datatype == 3)
				cout << "double " << it->first << " = " << it->second.u.value_double << " �ּ� : " << it->second.pnt << endl;
		}
	}
	return 0;
}