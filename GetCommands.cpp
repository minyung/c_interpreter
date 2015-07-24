#include"GetCommands.h"
#include"operators.h"

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
			vToken.push_back(token);
			vToken.push_back(";");
			token.clear();
		}
		//�������� ��ū�� �̾���δ�
		else{
			token += TMPcmd[here];
		}
	}
	return vToken;
}

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

	vToken = CreateToken(TMPcmd);


	string token, oldtoken;
	//�������� ��ū�� ù �κ�(if, int, while ��)�� ���� ȣ��Ǵ� �Լ��� �ٸ��Բ� ����
	
	for (int i = 0; i < vToken.size(); i++){
		cout << vToken[i].c_str() << " ";
	}
	for (int i = 0; i < vToken.size(); i++){
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
		
		if (token == ";"){
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
		else if (token == "if"){
		}
		else if (token == "for"){
		}
		/* ===============================
			������ ��ū ó�� - 2015.07.18 �ɹο� start
		   ===============================*/
		else if (prec != -1){
			PrecOper().infix_to_postfix(vToken, &i, var);
		}
		/* ===============================
			������ ��ū ó�� - 2015.07.18 �ɹο� end
		   ===============================*/
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