#include <vector>
#include "variable.h"

//���� 2���� �޴� �Լ�
bool getNumbers(vector<string> &postfix, int s, map<string, type> &var, double *num1, double *num2){
	//���� - ����
	if ((postfix[s - 2][0] == '-') || ('0' <= postfix[s - 2][0]) && (postfix[s - 2][0] <= '9') && ('0' <= postfix[s - 1][0]) && (postfix[s - 1][0] <= '9')){
		sscanf(postfix[s - 2].c_str(), "%lf", num1);
		sscanf(postfix[s - 1].c_str(), "%lf", num2);
	}
	//���� + ����
	else if ((var[postfix[s - 2]].pnt != 0) && ('0' <= postfix[s - 1][0]) && (postfix[s - 1][0] <= '9')){
		*num1 = var[postfix[s - 2]].getValue();
		sscanf(postfix[s - 1].c_str(), "%lf", num2);
	}
	//���� + ����
	else if ((var[postfix[s - 1]].pnt != 0) && ('0' <= postfix[s - 2][0]) && (postfix[s - 2][0] <= '9')){
		sscanf(postfix[s - 2].c_str(), "%lf", num1);
		*num2 = var[postfix[s - 1]].getValue();
	}
	//���� + ����
	else if ((var[postfix[s - 2]].pnt != 0) && (var[postfix[s - 1]].pnt != 0)){
		*num1 = var[postfix[s - 2]].getValue();
		*num2 = var[postfix[s - 1]].getValue();
	}
	else{ return false; }

	return true;
}

//'='
int calc_Eqauls(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";
	
	int s = *size;

	if (var[postfix[s - 2]].pnt == 0){
		cout << "[*] " << postfix[s - 2].c_str() << " : ���ǵ��� ���� �����Դϴ�." << endl;
		return -1;
	}
	//���� = ����
	if ((var[postfix[s - 2]].pnt != 0) && ('0' <= postfix[s - 1][0]) && (postfix[s - 1][0] <= '9')){
		sscanf(postfix[s - 1].c_str(), "%lf", &num2);
	}
	//���� = ����
	else if ((var[postfix[s-2]].pnt != 0) && (var[postfix[s-1]].pnt != 0)){
		num2 = var[postfix[s - 1]].getValue();
	}
	else { return -1; }

	var[postfix[s-2]].setValue(num2);
	
	result = 0;

	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;
	return result;
}

//'+'
int calc_Plus(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;

	getNumbers(postfix, s, var, &num1, &num2);

	result = num1 + num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}

int calc_Minus(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;

	getNumbers(postfix, s, var, &num1, &num2);

	result = num1 - num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}
//"*"
int calc_Multiple(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;

	getNumbers(postfix, s, var, &num1, &num2);

	result = num1 * num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}
//"/"
int calc_Division(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;

	getNumbers(postfix, s, var, &num1, &num2);

	result = num1 / num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}
//"%"
int calc_Percent(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;
	
	if (var[postfix[s - 2]].datatype == 3 || var[postfix[s - 1]].datatype == 3){
		cout << "[*] double���� %�� ����� �� �����ϴ�.\n" << endl;
		return -1;
	}
	getNumbers(postfix, s, var, &num1, &num2);

	result = (int)num1 % (int)num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}
//"<<" 
int calc_Shl(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;
	
	if (var[postfix[s - 2]].datatype == 3 || var[postfix[s - 1]].datatype == 3){
		cout << "[*] double���� << �� ����� �� �����ϴ�.\n" << endl;
		return -1;
	}
	getNumbers(postfix, s, var, &num1, &num2);

	result = (int)num1 << (int)num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}
//">>" 
int calc_Shr(vector<string> &postfix, int *size, map<string, type> &var){
	double num1, num2;
	double result = 0;
	char str[100] = "";

	int s = *size;

	if (var[postfix[s - 2]].datatype == 3 || var[postfix[s - 1]].datatype == 3){
		cout << "[*] double���� >> �� ����� �� �����ϴ�.\n" << endl;
		return -1;
	}
	getNumbers(postfix, s, var, &num1, &num2);
	result = (int)num1 >> (int)num2;
	postfix._Pop_back_n(3);

	sprintf(str, "%lf", result);
	postfix.push_back(str);
	*size -= 2;

	return result;
}