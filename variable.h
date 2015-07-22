#include<map>
#include<iostream>

#pragma once

using namespace std;

#define type_INT		1
#define type_CHAR		2
#define type_DOUBLE		3


struct type{
	int datatype;
	union{
		int		value_int;
		char	value_char;
		double	value_double;
	} u;
	int level;
	int pnt;
	type(){
		pnt = 0;
	}
	type(int dtype, int value, int lev, int p){
		datatype = dtype;
		u.value_int = value;
		level = lev;
		pnt = p;
	}
	type(int dtype, char value, int lev, int p){
		datatype = dtype;
		u.value_char = value;
		level = lev;
		pnt = p;
	}
	type(int dtype, double value, int lev, int p){
		datatype = dtype;
		u.value_double = value;
		level = lev;
		pnt = p;
	}
	double getValue(){
		if (datatype == 1){
			return u.value_int;
		}
		//char
		else if (datatype == 2){
			return u.value_char;
		}
		//double
		else if (datatype == 3){
			return u.value_double;
		}
	}
	void setValue(double num){
		//int
		if (datatype == 1){
			u.value_int = (int)num;
		}
		//char
		else if (datatype == 2){
			u.value_char = (char)num;
		}
		//double
		else if (datatype == 3){
			u.value_double = (double)num;
		}
	}
};





void PrintState(map<string, type> &var);