#pragma once
#include <iostream>
#include "Graph.h"
#include "BinTree.h"

using namespace std;

template <typename T>
bool isLeaf(const BinTree<T>& t, T x) {
	if (t.isEmpty()) {
		return false;
	}
	if (t.getRootData() == x && t.getLeftTree().isEmpty() && t.getRightTree().isEmpty()) {
		return true;
	}
	return isLeaf(t.getLeftTree(), x) || isLeaf(t.getRightTree(), x);
}

template <typename T>
void getLeaves(const BinTree<T>& t, LList<T>& leaves) {
	if (t.isEmpty()) {
		return;
	}
	if (isLeaf(t, t.getRootData())) {
		leaves.insertToEnd(t.getRootData());
	}
	getLeaves(t.getLeftTree(), leaves);
	getLeaves(t.getRightTree(), leaves);
}

//finds all paths from root to leaf in BinTree
template <typename T>
void findAllPathsHelper(const BinTree<T>& t, LList<T> path, LList<LList<T>>& paths) {
	if (t.isEmpty()) {
		return;
	}

	path.insertToEnd(t.getRootData());

	if (isLeaf(t, t.getRootData())) {
		paths.insertToEnd(path);
	}
	findAllPathsHelper(t.getLeftTree(), path, paths);
	findAllPathsHelper(t.getRightTree(), path, paths);
}

template <typename T>
void findAllPaths(const BinTree<T>& t, LList<LList<T>>& paths) {
	LList<T> path;
	findAllPathsHelper(t, path, paths);
}

//finds all paths from node with the same value as the root to the nodes with the same values as the leaves
template <typename T>
void allPathsDFS(Graph<T>& g, const T& start, const T& end,
	LList<T>& visited, LList<T>& path, LList<LList<T>>& allPaths) {

	path.insertToEnd(start);

	if (start == end) {
		allPaths.insertToEnd(path);
	}
	else {
		visited.insertToEnd(start);
		Node<T>* ptr = g.getVertexPointer(start);
		ptr = ptr->next;
		while (ptr != nullptr) {
			if (!visited.hasMember(ptr->data)) {
				allPathsDFS(g, ptr->data, end, visited, path, allPaths);
			}
			ptr = ptr->next;
		}
		T x;
		visited.deleteLast(x);
	}
	T y;
	path.deleteLast(y);
}

template <typename T>
void findAllPathsInGraph(Graph<T>& g, const BinTree<T>& t, LList<LList<T>>& allPaths) {
	if (g.isEmpty()) {
		return;
	}

	LList<T> leaves;
	getLeaves(t, leaves);

	LList<T> visited;
	LList<T> path;

	leaves.iterStart();
	Node<T>* tmp = leaves.iterNext();
	T start = t.getRootData();
	while (tmp != nullptr) {
		allPathsDFS(g, start, tmp->data, visited, path, allPaths);
		tmp = tmp->next;
	}
}

//list help functions 
template <typename T>
bool checkEqualLists(LList<T> l1, LList<T> l2) {
	if (l1.isEmpty() && l2.isEmpty()) {
		return true;
	}
	if (l1.isEmpty() || l2.isEmpty() 
		|| l1.length() != l2.length()) {

		return false;
	}
	l1.iterStart();
	Node<T>* tmp1 = l1.iterNext();
	l2.iterStart();
	Node<T>* tmp2 = l2.iterNext();
	while (tmp1 != nullptr) {
		if (tmp1->data != tmp2->data) {
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
}

template <typename T>
bool hasListMember(LList<LList<T>> list, LList<T> l) {
	if (list.isEmpty()) {
		return false;
	}
	list.iterStart();
	Node<LList<T>>* tmp = list.iterNext();
	while (tmp != nullptr) {
		if (checkEqualLists(tmp->data, l)) {
			return true;
		}
		tmp = list.iterNext();
	}
	return false;
}

//prints paths which exist in both tree and graph
template <typename T>
void printEqualPaths(const BinTree<T>& t, Graph<T>& g) {
	LList<LList<T>> treePaths;
	findAllPaths(t, treePaths);

	LList<LList<T>> graphPaths;
	findAllPathsInGraph(g, t, graphPaths);

	treePaths.iterStart();
	Node<LList<T>>* tmp = treePaths.iterNext();

	while (tmp != nullptr) {
		if (hasListMember(graphPaths, tmp->data)) {
			tmp->data.print();
		}
		tmp = treePaths.iterNext();
	}
}