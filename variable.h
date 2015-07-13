#include<map>
#include<string>
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
};
char datatype[3][12] = { "int", "char", "double" };

