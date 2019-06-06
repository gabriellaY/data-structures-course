#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class LList {
private:
	Node<T> *start, *end, *current;
	void copyList(LList<T> const&);
	void deleteList();
public:
	LList();
	LList(LList<T> const&);
	LList<T>& operator=(LList<T> const&);
	~LList();

	void iterStart(Node<T> *p = nullptr);
	Node<T>* iterNext();

	void insertToEnd(T const&);
	void insertAfter(Node<T>*, T const&);
	void insertBefore(Node<T>*, T const&);

	void deleteElem(Node<T> *, T&);
	bool deleteBefore(Node<T> *, T&);
	bool deleteAfter(Node<T> *, T&);
	void deleteLast(T&);

	bool isEmpty() const;
	bool hasMember(T x) const;

	void print() const;
	int length() const;
};

template <typename T>
LList<T>::LList() {
	start = current = end = nullptr;
}

template <typename T>
void LList<T>::copyList(LList<T> const& l) {
	start = end = nullptr;

	Node<T> *toCopy = l.start;
	while (toCopy != nullptr) {
		insertToEnd(toCopy->data);
		toCopy = toCopy->next;
	}
}

template <typename T>
void LList<T>::deleteList() {
	Node<T> *toDelete = start;
	while (start != nullptr) {
		toDelete = start;
		start = start->next;

		delete toDelete;
	}

	end = nullptr;
}

template <typename T>
LList<T>::LList(LList<T> const &l) {
	copyList(l);
}

template <typename T>
LList<T>& LList<T>::operator=(LList<T> const &l) {
	if (this != &l) {
		deleteList();
		copyList(l);
	}
	return *this;
}

template <typename T>
LList<T>::~LList() {
	deleteList();
}

template <typename T>
void LList<T>::iterStart(Node<T> *p) {
	if (p != nullptr) {
		current = p;
	}
	else {
		current = start;
	}
}

template <typename T>
Node<T>* LList<T>::iterNext() {
	Node<T> *result = current;
	if (current != nullptr) {
		current = current->next;
	}
	return result;
}

template <typename T>
void LList<T>::insertToEnd(T const &x) {
	Node<T> *toAdd = new Node<T>(x);

	if (isEmpty()) {
		start = toAdd;
	}
	else {
		end->next = toAdd;
	}
	end = toAdd;
}

template <typename T>
void LList<T>::insertAfter(Node<T> *p, T const &x) {

	if (p == nullptr) {
		std::cerr << "Invalid pointer";
		return;
	}

	p->next = new Node<T>(x, p->next);
	if (end == p) {
		end = p->next;
	}
}

template <typename T>
void LList<T>::insertBefore(Node<T> *p, T const &x) {

	if (p == nullptr) {
		std::cerr << "Invalid pointer";
		return;
	}

	if (start == p) {
		start = new Node<T>(x, p);
	}
	else {
		Node<T> *q = start;
		while (q->next != p)
			q = q->next;
		insertAfter(q, x);
	}
}

template <typename T>
bool LList<T>::deleteAfter(Node<T> *p, T &x) {
	if (p == nullptr) {
		std::cerr << "Invalid pointer";
		return false;
	}

	Node<T> *q = p->next;

	if (q != nullptr) {
		if (end == q) {
			end = p;
		}
		p->next = q->next;
		x = q->data;
		delete q;
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
inline void LList<T>::deleteLast(T& x) {
	iterStart();
	Node<T> *p = iterNext();
	while (p->next != nullptr) {
		p = iterNext();
	}
	deleteElem(p, x);
}

template <typename T>
void LList<T>::deleteElem(Node<T> *p, T &x) {
	if (p == nullptr) {
		std::cerr << "Invalid pointer";
		return;
	}

	if (p != start) {
		Node<T> *temp = start;
		while (temp->next != p)
			temp = temp->next;
		deleteAfter(temp, x);
	}
	else {
		x = p->data;

		if (start == end)
		{
			start = nullptr;
			end = nullptr;
		}
		else
			start = start->next;

		delete p;
	}
}

template <typename T>
bool LList<T>::deleteBefore(Node<T>* p, T &x)
{
	if (p == nullptr) {
		std::cerr << "Invalid pointer";
		return false;
	}

	if (p != start)
	{
		Node<T> *q = start;
		while (q->next != p)
			q = q->next;
		deleteElem(q, x);

		return true;
	}

	return false;
}


template <typename T>
bool LList<T>::isEmpty() const {
	return start == nullptr;
}

template <typename T>
void LList<T>::print() const {
	Node<T> *q = start;
	while (q != nullptr) {
		std::cout << q->data << ' ';
		q = q->next;
	}
	std::cout << std::endl;
}

template <typename T>
int LList<T>::length() const {
	Node<T> *q = start;
	int counter = 0;

	while (q != nullptr) {
		counter++;
		q = q->next;
	}

	return counter;
}

template<typename T>
bool LList<T>::hasMember(T x) const {
	if (isEmpty()) {
		return false;
	}

	Node<T>* tmp = start;

	while (tmp != nullptr) {
		if (tmp->data == x) {
			return true;
		}

		tmp = tmp->next;
	}
	return false;
}
