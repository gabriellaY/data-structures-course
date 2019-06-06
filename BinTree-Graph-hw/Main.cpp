#include <iostream>
#include "Functions.h"

using namespace std;

void testAllPathsFromRootToLeaf() {
	BinTree<char> a, b, c, d, e, f, g, h, n, empty;
	g.createWithData('g', empty, empty);
	h.createWithData('h', empty, empty);
	n.createWithData('n', empty, empty);
	c.createWithData('c', empty, empty);
	d.createWithData('d', h, empty);
	f.createWithData('f', n, empty);
	e.createWithData('e', d, g);
	b.createWithData('b', c, f);
	a.createWithData('a', b, e);

	cout << endl;

	//cout << boolalpha << isLeaf(a, 'h') << endl;
	//cout << boolalpha << isLeaf(a, 'e') << endl;

	LList<LList<char>> paths;
	findAllPaths(a, paths);

	paths.iterStart();
	Node<LList<char>>* tmp = paths.iterNext();
	while (tmp != nullptr) {
		tmp->data.print();
		tmp = paths.iterNext();
	}
}

void testGetLeaves() {
	BinTree<char> a, b, c, d, e, f, g, h, n, empty;
	g.createWithData('g', empty, empty);
	h.createWithData('h', empty, empty);
	n.createWithData('n', empty, empty);
	c.createWithData('c', empty, empty);
	d.createWithData('d', h, empty);
	f.createWithData('f', n, empty);
	e.createWithData('e', d, g);
	b.createWithData('b', c, f);
	a.createWithData('a', b, e);

	a.print();
	cout << endl;

	LList<char> leaves;
	getLeaves(a, leaves);
	leaves.print();
}

void testAllPathsInG() {
	Graph<char> g;
	
	g.addVertex('l');
	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('f');
	g.addVertex('c');
	g.addVertex('n');
	g.addVertex('a');
	g.addVertex('e');
	g.addVertex('g');
	
	g.addEdge('l', 'a');
	g.addEdge('a', 'b');
	g.addEdge('b', 'f');
	g.addEdge('b', 'c');
	g.addEdge('f', 'g');
	g.addEdge('n', 'a');
	g.addEdge('a', 'e');
	g.addEdge('e', 'b');
	g.addEdge('e', 'g');

	g.print();

	BinTree<char> a, b, c, d, e, f, g1, h, n, empty;
	g1.createWithData('g', empty, empty);
	h.createWithData('h', empty, empty);
	n.createWithData('n', empty, empty);
	c.createWithData('c', empty, empty);
	d.createWithData('d', h, empty);
	f.createWithData('f', n, empty);
	e.createWithData('e', d, g1);
	b.createWithData('b', c, f);
	a.createWithData('a', b, e);

	cout << endl;
	LList<LList<char>> allPaths;
	findAllPathsInGraph(g, a, allPaths);

	allPaths.iterStart();
	Node<LList<char>>* tmp = allPaths.iterNext();
	while (tmp != nullptr) {
		tmp->data.print();
		tmp = allPaths.iterNext();
	}
}

void testEqualPaths() {
	Graph<char> g;

	g.addVertex('l');
	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('f');
	g.addVertex('c');
	g.addVertex('n');
	g.addVertex('a');
	g.addVertex('e');
	g.addVertex('g');

	g.addEdge('l', 'a');
	g.addEdge('a', 'b');
	g.addEdge('b', 'f');
	g.addEdge('b', 'c');
	g.addEdge('f', 'g');
	g.addEdge('n', 'a');
	g.addEdge('a', 'e');
	g.addEdge('e', 'b');
	g.addEdge('e', 'g');

	BinTree<char> a, b, c, d, e, f, g1, h, n, empty;
	g1.createWithData('g', empty, empty);
	h.createWithData('h', empty, empty);
	n.createWithData('n', empty, empty);
	c.createWithData('c', empty, empty);
	d.createWithData('d', h, empty);
	f.createWithData('f', n, empty);
	e.createWithData('e', d, g1);
	b.createWithData('b', c, f);
	a.createWithData('a', b, e);

	printEqualPaths(a, g);
	//cout << endl;
}

int main() {

	//testAllPathsFromRootToLeaf();
	//testGetLeaves();
	//testAllPathsInG();
	testEqualPaths();

	system("pause");
	return 0;
}