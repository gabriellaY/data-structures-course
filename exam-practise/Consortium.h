#pragma once
#include "Company.h"

class Consortium : public Company {
private:
	Company** companies;
	int capacity;
	int size;
	int numberOfProjects;

	void copy(const Consortium& other) {
		capacity = other.capacity;
		size = other.size;
		numberOfProjects = other.numberOfProjects;
		companies = new Company*[capacity];
		for (int i = 0; i < size; i++) {
			companies[i] = other.companies[i]->clone();
		}
	}

	void del() {
		for (int i = 0; i < size; i++) {
			delete companies[i];
		}
		delete[] companies;
	}

	void resize() {
		Company** tmp = companies;
		capacity *= 2;
		companies = new Company*[capacity];
		for (int i = 0; i < size; i++) {
			companies[i] = tmp[i];
		}
		delete[] tmp;
	}

public:
	Consortium(char* _name = nullptr, char* _project = nullptr, int _capacity = 16, int _numberOfProjects = 0) : Company(_name, _project)  {
		capacity = _capacity;
		numberOfProjects = _numberOfProjects;
	}

	Consortium(const Consortium& other) {
		copy(other);
	}

	Consortium& operator = (const Consortium& other) {
		if (this != &other) {
			del();
			copy(other);
		}
		return *this;
	}

	~Consortium() {
		del();
	}

	void printStatus(ostream& os, int k) const {
		for (int i = 0; i < size; i++) {
			os << i + 1 << "." << companies[i]->get_name() << ", " << companies[i]->reliabilityRate(k) << endl;
		}
	}

	virtual void print(ostream& os) const {
		Company::print(os);
		os << "Number of projects: " << numberOfProjects << endl;
	}

	friend ostream& operator << (ostream& os, const Consortium& obj) {
		obj.print(os);
	}

	void add(Company* company) {
		if (size == capacity) {
			resize();
		}
		companies[size] = company;
		size++;
	}

	virtual double reliabilityRate(int k) {
		//...//...//...//...//
	}

	virtual bool perform(int project) {
		for (int i = 0; i < size; i++) {
			if (!companies[i]->perform(project))
				return false;
		}
		return true;
	}

	virtual Company* clone() const {
		return new Consortium(*this);
	}
};
