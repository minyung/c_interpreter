#include "operators.h"


string strOper = "()[]~!++--*/%<>=&*^|";

/* ������ Ȯ���ؼ� ��ū�� �־��ִ� �κ� start */
bool isOper(string cmd, int* here, string *sOper){
	string oper;
	int index = *here;
	char ch;	//temp ����

	// ù��°�� ������ �κ��� �ƴ϶�� false
	if (strOper.find(cmd[index]) == -1){
		return false;
	}

	// �´ٸ� oper �� �־��ش�.
	oper += cmd[index];

	ch = cmd[index+1];	//�ι�° ���ڸ� ch �� �����Ͽ��ش�.

	/* ��ȣó�� start */
	// oper[0] = ��ȣ�� �� �ڿ� ��ȣ�� ���� �ȴ�
	if ((oper == "(") || (oper == "[")){; }
	else if ((oper == ")") || (oper == "]") || (ch == '(') || (ch == '[')){; }
	/* ��ȣó�� end */
	else if (strOper.find(ch) == -1){ ; }	// �ι�° ���ڵ� Ư�����ڰ� �ƴ϶��?
	else if (('0' <= ch) && (ch <= '9')){ ; }		//�ڿ� ���ڰ� ������ �����ڰ� �����ٴ� ���� �˷���
	else if (ch == ' '){ ; }		//�ڿ� ������ �ִٸ� �����ڰ� �����ٴ� ���� �˷���
	else{
		oper += ch;	(*here)++;
	}
	*sOper = oper;
	return true;
}
/* ������ Ȯ���ؼ� ��ū�� �־��ִ� �κ� end */

/* ��ū�� ���������� Ȯ������ */
bool isTokenOper(string token){
	return 0;
}