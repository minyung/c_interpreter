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