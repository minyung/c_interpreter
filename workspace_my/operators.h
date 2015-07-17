#include<vector>
#include<stack>

using namespace std;

class PrecOper {
	vector<string> precedenceOper;
public:
	PrecOper(){
		precedenceOper.push_back("( ) [ ] -> ");
		precedenceOper.push_back("++ -- ~ ! ");
		precedenceOper.push_back("* / % ");
		precedenceOper.push_back("+ - ");
		precedenceOper.push_back("<< >> ");
		precedenceOper.push_back("< <= > >= ");
		precedenceOper.push_back("== != ");
		precedenceOper.push_back("& ");
		precedenceOper.push_back("^ ");
		precedenceOper.push_back("| ");
		precedenceOper.push_back("&& ");
		precedenceOper.push_back("|| ");
		precedenceOper.push_back("? : ");
		precedenceOper.push_back("= += -= *= /= %= &= ^= |= <<= >>= ");
		precedenceOper.push_back(", ");
	}
	int GetPrecedence(string str){
		for (int i = 0; i < 15; i++){
			if (precedenceOper[i].find(str) != -1){
				return i + 1;
			}
		}
		return -1;
	}
};
class Mystack {
private:
	stack<double> st;
public:
	void push(double n) { st.push(n); }		//push
	int size(){ return (int)st.size(); }	//size
	bool empty() { return st.empty(); }		//empty
	double pop() {
		if (st.empty())	puts("stack underflow");
		double d = st.top();		//최상위 값
		st.pop(); return d;
	}
};

bool isOper(string cmd, int* here, string *sOper);