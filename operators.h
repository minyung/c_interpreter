#include<vector>
#include<stack>
#include"variable.h"
#include"calcfunc.h"

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
		stack<string> st;
		int index = *pIndex;
		int varNum = var[infix[index - 1]].pnt;


		postfix.push_back(infix[index - 1]);

		// 1. ++ 와 --가 변수 앞에 있는 경우
		if (infix[index] == "(" || infix[index] == "++" || infix[index] == "--"){
			postfix.pop_back();
		}
		// 2. 앞 부분이 숫자일 경우
		else if ('0' <= infix[index - 1][0] && infix[index-1][0] <= '9'){
//			cout << "[*] " << infix[index-1].c_str() << " : 숫자입니다. " << endl;
		}
		// 3. 정의되지 않은 변수 일 경우 return 1;
		else if (varNum == 0){
			cout << "[*] " << infix[index - 1].c_str() << " : 정의되지 않은 변수입니다." << endl;
			return 1;
		}
			
		st.push(infix[index]);
		for (int i = index + 1; i < infix.size(); i++){
		//	printf("%s ", infix[i].c_str());
			
			// 넣는 값이 숫자라면 바로 postfix에 출력
			if ('0' <= infix[i][0] && infix[i][0] <= '9'){
				postfix.push_back(infix[i]);
			}
			// 스택에 아무것도 없다면?
			else if (st.empty()){
				postfix.push_back(infix[i]);
			}
			//여는 괄호일경우엔
			else if (infix[i] == "("){
				st.push(infix[i]);
			}
			//닫는 괄호일경우엔
			else if (infix[i] == ")"){
				if (st.empty()){
					cout << "[*] '('가 없습니다. " << endl;
					return 2;
				}
				while (st.top() != "("){
					postfix.push_back(st.top());
					st.pop();
					if (st.empty()){
						cout << "[*] '('가 없습니다. " << endl;
						return 2;
					}
				}
				st.pop();	//"("를 빼준다.
			}
			// 스택.top 이 우선순위가 더 높다면?
			else if (GetPrecedence(infix[i]) >= GetPrecedence(st.top())){
				while ((!st.empty()) && (st.top() != "(") && (GetPrecedence(infix[i]) >= GetPrecedence(st.top()))){
					postfix.push_back(st.top());
					st.pop();
				}
				st.push(infix[i]);

			}else{
				if (infix[i] == ";"){
					printf(";\n");
					break;
				}
				st.push(infix[i]);
			}
		} 

		//마지막 스택 정리
		while (!st.empty()){
			postfix.push_back(st.top());
			st.pop();
		}
		
		printf("\n----------------\n");
		for (int i = 0; i < postfix.size(); i++){
			printf("%s ", postfix[i].c_str());
		}printf("\n-------------------\n");

		*pIndex += postfix.size();

		calc(var);

		return 0;
	}


	int calc(map<string, type> &var){
		double num1, num2;
		double result = 0;
		vector<string> postfix_temp;
		int temp_size=-1;
		char str[100] = "";

		for (int i = 0; i < postfix.size(); i++){
			
			if (postfix[i] == "")	continue;

			postfix_temp.push_back(postfix[i]);
			temp_size++;

			//'=' 처리
			if (postfix_temp[temp_size] == "="){
				result = calc_Eqauls(postfix_temp, &temp_size, var);
			}
			//'+' 처리
			else if (postfix_temp[temp_size] == "+"){
				result = calc_Plus(postfix_temp, &temp_size, var);
			}
			//'-' 처리
			else if (postfix_temp[temp_size] == "-"){
				result = calc_Minus(postfix_temp, &temp_size, var);
			}
			//'*' 처리
			else if (postfix_temp[temp_size] == "*"){
				result = calc_Multiple(postfix_temp, &temp_size, var);
			}
			//'/' 처리
			else if (postfix_temp[temp_size] == "/"){
				result = calc_Division(postfix_temp, &temp_size, var);
			}
			//'%' 처리
			else if (postfix_temp[temp_size] == "%"){
				result = calc_Percent(postfix_temp, &temp_size, var);
			}
			//'<<' 처리
			else if (postfix_temp[temp_size] == "<<"){
				result = calc_Shl(postfix_temp, &temp_size, var);
			}
			//'>>' 처리
			else if (postfix_temp[temp_size] == ">>"){
				result = calc_Shr(postfix_temp, &temp_size, var);
			}
			else	continue;
			
			cout << "result: " << result << endl;
		}
		return 1;

	}
};

bool isOper(string cmd, int* here, string *sOper);