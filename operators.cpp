#include "operators.h"


string strOper = "()[]~!++--*/%<>=&*^|,";

/* 연산자 확인해서 토큰에 넣어주는 부분 start */
bool isOper(string cmd, int* here, string *sOper){
	string oper;
	int index = *here;
	char ch;	//temp 역할

	// 첫번째가 연산자 부분이 아니라면 false
	if (strOper.find(cmd[index]) == -1){
		return false;
	}

	// 맞다면 oper 에 넣어준다.
	oper += cmd[index];	(*here)++;

	ch = cmd[index+1];	//두번째 문자를 ch 에 저장하여준다.

	/* 괄호처리 start */
	// oper[0] = 괄호일 때 뒤에 괄호가 오면 안댐
	if ((oper[0] == '(') || (oper[0] == '[')){
		if ((ch == '(') || (ch == '[')){
			return true;
		}
	}
	/* 괄호처리 end */
	else if (strOper.find(ch) == -1){}	// 두번째 문자도 특수문자가 아니라면?
	else if (('0' <= ch) && (ch <= '9')){}		//뒤에 숫자가 있으면 연산자가 끝났다는 것을 알려줌
	else if (ch == ' '){}		//뒤에 공백이 있다면 연산자가 끝났다는 것을 알려줌
	else{
		oper += ch;	(*here)++;
	}
	*sOper = oper;
	return true;
}
/* 연산자 확인해서 토큰에 넣어주는 부분 end */

/* 토큰이 연산자인지 확인하자 */
bool isTokenOper(string token){
	return 0;
}