#pragma once
#include <iostream>
using namespace std;

class Company {
private:
	char* name;
	char* project;

	void copy(const Company& other) {
		name = new char[strlen(other.name) + 1];
		strcpy_s(name, strlen(other.name) + 1, other.name);

		project = new char[strlen(other.project) + 1];
		strcpy_s(project, strlen(other.project) + 1, other.project);
	}

	void del() {
		delete[] name;
		delete[] project;
	}

public:
	Company(char* _name = nullptr, char* _project = nullptr) {
		name = new char[strlen(_name) + 1];
		strcpy_s(name, strlen(_name) + 1, _name);

		project = new char[strlen(_project) + 1];
		strcpy_s(name, strlen(_project) + 1, _project);
	}

	Company(const Company& other) {
		copy(other);
	}

	Company& operator = (const Company& other) {
		if (this != &other) {
			del();
			copy(other);
		}
		return *this;
	}

	virtual ~Company() {
		del();
	}

	const char* get_name() const {
		return name;
	}

	const char* get_project() const {
		return project;
	}

	virtual void print(ostream& os) const = 0;
	virtual Company* clone() const = 0;

	virtual double reliabilityRate(int k) = 0;
	virtual bool perform(int project) = 0;
};