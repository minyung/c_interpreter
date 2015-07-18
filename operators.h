#include<vector>
#include<stack>
#include"variable.h"

using namespace std;

class Mystack {
private:
	stack<string> st;
public:
	void push(string n) { st.push(n); }		//push
	int size(){ return (int)st.size(); }	//size
	bool empty() { return st.empty(); }		//empty
	string pop() {
		if (st.empty())	puts("stack underflow");
		string d = st.top();		//최상위 값
		st.pop(); return d;
	}
};


class PrecOper {
	vector<string> precedenceOper;
	vector<string> postfix;
public:
	PrecOper(){
		this->precedenceOper.push_back("( ) [ ] -> ");
		this->precedenceOper.push_back("++ -- ~ ! ");
		this->precedenceOper.push_back("* / % ");
		this->precedenceOper.push_back("+ - ");
		this->precedenceOper.push_back("<< >> ");
		this->precedenceOper.push_back("< <= > >= ");
		this->precedenceOper.push_back("== != ");
		this->precedenceOper.push_back("& ");
		this->precedenceOper.push_back("^ ");
		this->precedenceOper.push_back("| ");
		this->precedenceOper.push_back("&& ");
		this->precedenceOper.push_back("|| ");
		this->precedenceOper.push_back("? : ");
		this->precedenceOper.push_back("= += -= *= /= %= &= ^= |= <<= >>= ");
		this->precedenceOper.push_back(", ");
	}
	int GetPrecedence(string str){
		if (str == "\0")					return -1;
		else if (str == "+" || str == "-")	return 4;	// '+' 와 '-'는 '++', '--' 가 있기 때문에 따로 처리를 해주자.
		for (int i = 0; i < precedenceOper.size(); i++){
			if (this->precedenceOper[i].find(str) != -1){
				return i + 1;
			}
		}
		return -1;
	}
	int infix_to_postfix(vector<string> infix, int *pIndex, map<string, type> &var){
		Mystack stack;
		int index = *pIndex;
		int varNum = var[infix[index - 1]].pnt;
		
		// 1. 정의되지 않은 변수 일 경우 예외
		if (varNum == 0){
			cout << "[*] " << infix[index - 1].c_str() << " : 정의되지 않은 변수입니다." << endl;
			return 1;
		}
		
		postfix.push_back(infix[index - 1]);
	
		for (int i = index; i < infix.size(); i++){
			cout << "+_+: " << infix[i].c_str() << endl;
		}
		return 0;
	}
};

bool isOper(string cmd, int* here, string *sOper);