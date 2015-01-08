#ifndef __syntax_check__
#define __syntax_check__

#include "scanner.h"
#include "token.h"
#include "Node.h"

using namespace std;

enum fail{
	CORRECT, FAIL
};
typedef fail FailureBit;

class Syntax_Check {
public:
	Syntax_Check(char*);
	~Syntax_Check();

private:
	Scanner* scannerpointer;
	void prog();
	TreeNode decls();
	TreeNode decl();
	TreeNode array();
	TreeNode statements();
	TreeNode statement();
	TreeNode exp();
	TreeNode exp2();
	TreeNode index();
	TreeNode op_exp();
	TreeNode op();
	Token* actToken;
	State tokenType;
	TreeNode rootNode;
	FailureBit failBit;


};

#endif
