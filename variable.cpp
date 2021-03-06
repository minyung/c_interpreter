#include"variable.h"
void PrintState(map<string, type> &var){
	map<string, type>::iterator it;
	//한 줄 처리가 끝나면 현재의 상황을 출력
	puts("//-----------------//");
	puts("현재 변수 목록");
	
	for (it = var.begin(); it != var.end(); it++){
		if (it->second.datatype == 1)
			cout << "int " << it->first.c_str() << " = " << it->second.u.value_int << " 주소 : " << it->second.pnt << endl;
		if (it->second.datatype == 2)
			cout << "char " << it->first.c_str() << " = " << it->second.u.value_char << " 주소 : " << it->second.pnt << endl;
		if (it->second.datatype == 3)
			cout << "double " << it->first.c_str() << " = " << it->second.u.value_double << " 주소 : " << it->second.pnt << endl;
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