#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <utility>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "scheduleItem.h"
using namespace std;
class schedule : public scheduleItem
{
private:
	map<string, scheduleItem> scheduleMap;
public:
	schedule() {};

	void initSchedule(ifstream& inFile) {
		if (!inFile) {
			cerr << "Error opening the input file.";
		};

		string line;
		getline(inFile, line);

		while (getline(inFile, line)) {
			stringstream ss(line);
			string subject, catalog, section, component, session, units, totEnrl, capEnrl, instructor;
			getline(ss, subject, ',');
			getline(ss, catalog, ',');
			getline(ss, section, ',');
			getline(ss, component, ',');
			getline(ss, session, ',');
			getline(ss, units, ',');
			getline(ss, totEnrl, ',');
			getline(ss, capEnrl, ',');
			getline(ss, instructor, ',');

			int unitsStr = stoi(units);
			int totEnrlStr = stoi(totEnrl);
			int capEnrlStr = stoi(capEnrl);

			string key = subject + "_" + catalog + "_" + section;
			scheduleItem item(subject, catalog, section, component, session, unitsStr, totEnrlStr, capEnrlStr, instructor);
			addEntry(key, item);
		}

		inFile.close();
	}

	void addEntry(string key, scheduleItem& item) {
		scheduleMap.insert(make_pair(key, item));
	}

	void printHeader() const {
		cout << "Subject " << " Catalog " << " Section " << " Component " << " Session " << " Units " << " TotEnrl " << " CapEnrl " << " Instructor " << endl;
	}

	void print() const {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			cout << left
				<< setw(10) << item.getSubject()
				<< setw(10) << item.getCatalog()
				<< setw(10) << item.getSection()
				<< setw(14) << item.getComponent()
				<< setw(10) << item.getSession()
				<< setw(10) << item.getUnits()
				<< setw(10) << item.getTotEnrl()
				<< setw(10) << item.getCapEnrl()
				<< setw(27) << item.getInstructor()
				<< endl;
		}
	}

	scheduleItem findBySubject(string& subj) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			if (subj == item.getSubject()) {
				item.print();
			}
		}
	}
	scheduleItem findBySubjectAndCatalog(string& subj, string& cat) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			if (subj == item.getSubject() && cat == item.getCatalog()) {
				item.print();
			}
		}
	}

	scheduleItem findByInstructor(string& lastName) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			string instructorFullName = item.getInstructor();
			size_t comma = instructorFullName.find(',');
			if (comma != string::npos) {
				string instructorLast = instructorFullName.substr(0,comma);
				if (instructorLast == lastName) {
					item.print();
				}
			}
		}
	}

};

