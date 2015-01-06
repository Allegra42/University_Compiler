#ifndef __syntax_check__
#define __syntax_check__

#include "scanner.h"
#include "token.h"

using namespace std;

class Syntax_Check {
public:
	Syntax_Check(char*);
	~Syntax_Check();

private:
	Scanner* scannerpointer;
	void prog();
	void decls();
	void decl();
	void array();
	void statements();
	void statement();
	void exp();
	void exp2();
	void index();
	void op_exp();
	void op();
	Token* actToken;
	State tokenType;



};

#endif
