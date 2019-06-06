#include "Functions.h"

int main() {
	char expr[10] = "*+-a4b+3a";
	char* ptr = expr;

	//changeExpression test
	char* newExpr = changeExpression(ptr);

	//creating tree test
	BinTree<char> t = createExprTree(newExpr);
	cout << endl;
	cout << "The expression tree is: ";
	t.print();
	cout << endl << endl;

	//postfix expression test
	cout << "Postfix of the expression: ";
	postfixExpression(expr);
	cout << endl << endl;

	//evaluating expression tree test
	cout << "The evaluation of the expression is: " << calculateExpressionTree(t) << endl << endl;

	system("pause");
	return 0;
}