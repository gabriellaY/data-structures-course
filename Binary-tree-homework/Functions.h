#pragma once
#include <iostream>
#include "BinTree.h"
#include <stack>

using namespace std;

//à)
BinTree<char> createExprTree(char* &expr) {

	BinTree<char> empty;
	BinTree<char> left;
	BinTree<char> right;
	BinTree<char> resultTree;

	if (expr == nullptr) {
		return BinTree<char>();
	}

	char elem = *expr;
	if (elem >= '0' && elem <= '9' || elem >= 'a' && elem <= 'z') {
		resultTree.createWithData(elem, empty, empty);
		return resultTree;
	}
	else {
		left = createExprTree(++expr);
		right = createExprTree(++expr);
		resultTree.createWithData(elem, left, right);
		return resultTree;
	}
}

//á) 
//postorder traversal (left-right-root)
void postorder(BinTree<char> expressionTree) {
	if (expressionTree.isEmpty()) {
		return;
	}
	postorder(expressionTree.getLeftTree());
	postorder(expressionTree.getRightTree());
	cout << expressionTree.getRootData() << " ";
}

void postfixExpression(char* expr) {
	BinTree<char> tree = createExprTree(expr);
	postorder(tree);
}

//â)
//replacing symbols with actual values
char* changeExpression(char* expr) {
	char* changed = new char[strlen(expr) + 1]; //expression with numbers only
	char inputNumbers[26]; //array with the entered values for every letter, initialised with '#'
	for (int i = 0; i < 25; i++) {
		inputNumbers[i] = '#';
	}

	for (int i = 0; i < strlen(expr); i++) {
		if (expr[i] >= 'a' && expr[i] <= 'z') {
			if (inputNumbers[expr[i] - 'a'] != '#') {
				changed[i] = inputNumbers[expr[i] - 'a'];
			}
			else {
				char value;
				cout << "Please, input a value of " << expr[i] << endl;
				cin >> value;
				changed[i] = value;
				inputNumbers[expr[i] - 'a'] = value;
			}
		}
		else {
			changed[i] = expr[i];
		}
	}
	changed[strlen(expr)] = '\0';
	return changed;
}

int calculateExpressionTree(BinTree<char> tree) {
	if (tree.isEmpty()) {
		return 0;
	}
	char elem = tree.getRootData();

	if (tree.getLeftTree().isEmpty() && tree.getRightTree().isEmpty()) {
		return elem - '0';
	}

	int left = calculateExpressionTree(tree.getLeftTree());
	int right = calculateExpressionTree(tree.getRightTree());

	if (elem == '+') {
		return left + right;
	}
	else if (elem == '-') {
		return left - right;
	}
	else if (elem == '*') {
		return left * right;
	}
}

int calculateExpr(char* expr) {
	char* newExpr = changeExpression(expr);
	BinTree<char> tree = createExprTree(newExpr);

	return calculateExpressionTree(tree);
} 