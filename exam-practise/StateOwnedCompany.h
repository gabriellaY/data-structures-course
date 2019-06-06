#pragma once
#include "Company.h"

class StateOwnedCompany : public Company {
private:
	int numberOfProjects;
public:
	StateOwnedCompany(char* _name = nullptr, char* _project = nullptr, int _numberOfProjects = 0) : Company(_name, _project) {
		numberOfProjects = _numberOfProjects;
	}

	void print(ostream& os) const {
		Company::print(os);
		os << "Number of projects: " << numberOfProjects << endl;
	}

	friend ostream& operator << (ostream& os, const StateOwnedCompany& obj) {
		obj.print(os);
		return os;
	}

	virtual bool perform(int project) {
		if (project < numberOfProjects - 1) {
			numberOfProjects++;
			return true;
		}
		return false;
	}

	int count_successful_projects(int k) {
		k = 20;
		int success = 0;
		for (int i = 0; i < numberOfProjects; i + k) {
			success++;
		}
		return success;
	}

	virtual double reliabilityRate(int k) {
		k = 20;
		if (numberOfProjects == 0) {
			return 0;
		}
		return (double)count_successful_projects(k) / numberOfProjects;
	}

	virtual Company* clone() const {
		return new StateOwnedCompany(*this);
	}
};