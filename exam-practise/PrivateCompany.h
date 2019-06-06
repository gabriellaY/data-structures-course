#pragma once
#include "Company.h"

class PrivateCompany : public Company {
	int numberOfProjects;
	int k;

public:
	PrivateCompany(char* _name = nullptr, char* _project = nullptr, int _numberOfProjects = 0, int _k = 0) : Company(_name, _project) {
		numberOfProjects = _numberOfProjects;
		k = _k;
	}
	
	void print(ostream& os) const {
		Company::print(os);
		os	<< "Number of projects: " << numberOfProjects << endl;
	}

	friend ostream& operator << (ostream& os, const PrivateCompany& obj) {
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
		int success = 0;
		for (int i = 0; i < numberOfProjects; i + k) {
			success++;
		}
		return success;
	}

	virtual double reliabilityRate(int k) {
		if (numberOfProjects == 0) {
			return 0;
		}
		return (double) count_successful_projects(k) / numberOfProjects;
	}

	virtual Company* clone() const {
		 return new PrivateCompany(*this);
	}
};