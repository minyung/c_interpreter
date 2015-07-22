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
		string d = st.top();		//�ֻ��� ��
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
		else if (str == "+" || str == "-")	return 4;	// '+' �� '-'�� '++', '--' �� �ֱ� ������ ���� ó���� ������.

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

		// 1. ++ �� --�� ���� �տ� �ִ� ���
		if (infix[index] == "(" || infix[index] == "++" || infix[index] == "--"){
			postfix.pop_back();
		}
		// 2. �� �κ��� ������ ���
		else if ('0' <= infix[index - 1][0] && infix[index-1][0] <= '9'){
//			cout << "[*] " << infix[index-1].c_str() << " : �����Դϴ�. " << endl;
		}
		// 3. ���ǵ��� ���� ���� �� ��� return 1;
		else if (varNum == 0){
			cout << "[*] " << infix[index - 1].c_str() << " : ���ǵ��� ���� �����Դϴ�." << endl;
			return 1;
		}
			
		st.push(infix[index]);
		for (int i = index + 1; i < infix.size(); i++){
		//	printf("%s ", infix[i].c_str());
			
			// �ִ� ���� ���ڶ�� �ٷ� postfix�� ���
			if ('0' <= infix[i][0] && infix[i][0] <= '9'){
				postfix.push_back(infix[i]);
			}
			// ���ÿ� �ƹ��͵� ���ٸ�?
			else if (st.empty()){
				postfix.push_back(infix[i]);
			}
			//���� ��ȣ�ϰ�쿣
			else if (infix[i] == "("){
				st.push(infix[i]);
			}
			//�ݴ� ��ȣ�ϰ�쿣
			else if (infix[i] == ")"){
				if (st.empty()){
					cout << "[*] '('�� �����ϴ�. " << endl;
					return 2;
				}
				while (st.top() != "("){
					postfix.push_back(st.top());
					st.pop();
					if (st.empty()){
						cout << "[*] '('�� �����ϴ�. " << endl;
						return 2;
					}
				}
				st.pop();	//"("�� ���ش�.
			}
			// ����.top �� �켱������ �� ���ٸ�?
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

		//������ ���� ����
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

			//'=' ó��
			if (postfix_temp[temp_size] == "="){
				result = calc_Eqauls(postfix_temp, &temp_size, var);
			}
			//'+' ó��
			else if (postfix_temp[temp_size] == "+"){
				result = calc_Plus(postfix_temp, &temp_size, var);
			}
			//'-' ó��
			else if (postfix_temp[temp_size] == "-"){
				result = calc_Minus(postfix_temp, &temp_size, var);
			}
			//'*' ó��
			else if (postfix_temp[temp_size] == "*"){
				result = calc_Multiple(postfix_temp, &temp_size, var);
			}
			//'/' ó��
			else if (postfix_temp[temp_size] == "/"){
				result = calc_Division(postfix_temp, &temp_size, var);
			}
			//'%' ó��
			else if (postfix_temp[temp_size] == "%"){
				result = calc_Percent(postfix_temp, &temp_size, var);
			}
			//'<<' ó��
			else if (postfix_temp[temp_size] == "<<"){
				result = calc_Shl(postfix_temp, &temp_size, var);
			}
			//'>>' ó��
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