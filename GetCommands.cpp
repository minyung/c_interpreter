#include"GetCommands.h"

COMMAND GetCmd(map<string, type> &var, int &level, int &pointer, const vector<COMMAND> &command){
	COMMAND ret;
	char buf[120];
	string TMPcmd;
	gets(buf);
	TMPcmd = buf;
	if (TMPcmd.back() != ';'){
		puts("�����ݷ�(;)���� ������ �ʽ��ϴ�!");
		ret.level = -1;
		return ret;
	}

	//Ŀ�ǵ带 ��ǥ ������ ������ ���Ϳ� ����
	vector<string> vToken;
	string token;

	for (int here = 0; here < TMPcmd.length(); here++){
		//�����ڸ� ��ū�� ���� �����ڵ� ť�� �ִ´�
		if (TMPcmd[here] == '=' || TMPcmd[here] == '+'){
			vToken.push_back(token);
			token.clear();

			token += TMPcmd[here];
			vToken.push_back(token);
			token.clear();
		}
		//����� �׳� �Ѿ��
		else if (TMPcmd[here] == ' '){
			if (token != "") vToken.push_back(token);
			token.clear();
			continue;
		}
		//��ǥ�� �����ݷ��̸� ��ū�� ���´�
		else if (TMPcmd[here] == ',' || TMPcmd[here] == ';'){
			vToken.push_back(token);
			token.clear();
		}
		//�������� ��ū�� �̾���δ�
		else{
			token += TMPcmd[here];
		}
	}


	token.clear();
	string oldtoken;
	//�������� ��ū�� ù �κ�(if, int, while ��)�� ���� ȣ��Ǵ� �Լ��� �ٸ��Բ� ����
	for (int i = 0; i < vToken.size(); i++){
		token = vToken[i];
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
	}
	
	if (TMPcmd.back() == '{') level++;
	else if (TMPcmd.back() == '}') level--;

	ret = COMMAND(TMPcmd, level);
	return ret;
}