#include"variable.h"
void PrintState(map<string, type> &var){
	map<string, type>::iterator it;
	//�� �� ó���� ������ ������ ��Ȳ�� ���
	puts("//-----------------//");
	puts("���� ���� ���");
	
	for (it = var.begin(); it != var.end(); it++){
		if (it->second.datatype == 1)
			cout << "int " << it->first.c_str() << " = " << it->second.u.value_int << " �ּ� : " << it->second.pnt << endl;
		if (it->second.datatype == 2)
			cout << "char " << it->first.c_str() << " = " << it->second.u.value_char << " �ּ� : " << it->second.pnt << endl;
		if (it->second.datatype == 3)
			cout << "double " << it->first.c_str() << " = " << it->second.u.value_double << " �ּ� : " << it->second.pnt << endl;
	}
}

bool isValidName(string str){
	if ('0' <= str.front() && str.front() <= '9')
		return false;

	char check[][8] = { "if", "else", "for", "while",
		"int", "char", "double" };

	for (int i = 0; i < 7; i++){
		if (check[i] == str) return false;
	}
	return true;
}