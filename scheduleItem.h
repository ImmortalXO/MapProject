#pragma once
#include <iostream>
#include <string>
using namespace std;
class scheduleItem
{
private:
	string subject; 
	string catalog;
	string section;
	string component;
	string session;
	int units;
	int totEnrl; 
	int capEnrl; 
	string instructor;
public:
	scheduleItem(string subject = "", string catalog = "", string section = "", string component = "",
		string session = "", int units = 0, int totEnrl = 0, int capEnrl = 0, string instructor = "") : subject(subject), catalog(catalog), section(section),
		component(component), session(session), units(units), totEnrl(totEnrl), capEnrl(capEnrl), instructor(instructor)
	{};

	string getSubject() const { return subject; };
	string getCatalog() const { return catalog; };
	string getSection() const { return section; };
	string getComponent() const { return component; };
	string getSession() const { return session; };
	int getUnits() const { return units; };
	int getTotEnrl() const { return totEnrl; };
	int getCapEnrl() const { return capEnrl; };
	string getInstructor() const { return instructor.substr(1); };

	bool operator==(const scheduleItem& other) const {
		return (subject == other.subject && catalog == other.catalog && section == other.section);
	}

	bool operator!=(const scheduleItem& other) const {
		return !(*this == other);
	}

	bool operator>=(const scheduleItem& other) const {
		if (subject > other.subject) {
			return true;
		}
		else if (subject == other.subject) {
			if (catalog > other.catalog) {
				return true;
			}
			else if (catalog == other.catalog) {
				return section >= other.section;
			}
		}
		return false;
	}

	void print() const {
		cout << left
			<< setw(10) << subject
			<< setw(10) << catalog
			<< setw(10) << section
			<< setw(10) << component
			<< setw(10) << session
			<< setw(8) << units
			<< setw(8) << totEnrl
			<< setw(6) << capEnrl
			<< setw(15) << instructor.substr(1)
			<< endl;
	}


};

