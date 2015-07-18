#include"GetCommands.h"
#include"operators.h"

vector<string> CreateToken(string TMPcmd){
	vector<string> vToken;
	string token;
	for (int here = 0; here < TMPcmd.length(); here++){
		//연산자면 토큰을 끊고 연산자도 큐에 넣는다
		/* ===============================
			연산자 토큰 분리 - 2015.07.18 심민영 start
		   ===============================*/
		string sOper;
		if (isOper(TMPcmd, &here, &sOper)){
			vToken.push_back(token);
			token.clear();

	//		cout << sOper << endl;

			token += sOper;
			vToken.push_back(token);
			token.clear();

		}
		/* ===============================
		     연산자 토큰 분리 - 2015.07.18 심민영 end
		   ===============================*/
		//띄어쓰기면 그냥 넘어간다
		else if (TMPcmd[here] == ' '){
			if (token != "") vToken.push_back(token);
			token.clear();
			continue;
		}
		//쉼표나 세미콜론이면 토큰을 끊는다
		else if (TMPcmd[here] == ',' || TMPcmd[here] == ';'){
			vToken.push_back(token);
			token.clear();
		}
		//나머지는 토큰에 이어붙인다
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
		puts("세미콜론(;)으로 끝나지 않습니다!");
		ret.level = -1;
		return ret;
	}

	//커맨드를 쉼표 단위로 나누어 벡터에 저장
	vector<string> vToken;

	vToken = CreateToken(TMPcmd);


	string token, oldtoken;
	//나누어진 토큰의 첫 부분(if, int, while 등)에 따라 호출되는 함수가 다르게끔 설정
	for (int i = 0; i < vToken.size(); i++){
		token = vToken[i];

		cout << token << endl;

		//토큰의 첫 부분이 변수의 자료형이면 뒷 부분은 반드시 변수의 이름이 나온다
		/*변수 타입 구분
		1 == int
		2 == char
		3 == double
		*/
		/* ===============================
			연산자 토큰 처리 - 2015.07.18 심민영 start
		   ===============================*/
		int prec = PrecOper().GetPrecedence(token);
		/* ===============================
			연산자 토큰 처리 - 2015.07.18 심민영 end
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
			연산자 토큰 처리 - 2015.07.18 심민영 start
		   ===============================*/
		else if (prec != -1){
			cout << token << " " << prec << endl;
			PrecOper().infix_to_postfix(vToken, &i, var);
		}
		/* ===============================
			연산자 토큰 처리 - 2015.07.18 심민영 end
		   ===============================*/
		// 토큰이 변수 선언, if, for, while, 연산도 아니면 변수 이름인 것이다
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