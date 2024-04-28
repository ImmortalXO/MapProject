#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <utility>
#include <iomanip>
#include <algorithm>
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
			string dummy1, dummy2, dummy3;
			getline(ss, subject, ',');
			getline(ss, catalog, ',');
			getline(ss, section, ',');
			getline(ss, component, ',');
			getline(ss, session, ',');
			getline(ss, dummy1, ',');
			getline(ss, units, ',');
			getline(ss, totEnrl, ',');
			getline(ss, capEnrl, ',');
			getline(ss, dummy3, ',');
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
				<< setw(10) << item.getComponent()
				<< setw(10) << item.getSession()
				<< setw(8) << item.getUnits()
				<< setw(8) << item.getTotEnrl()
				<< setw(6) << item.getCapEnrl()
				<< setw(8) << item.getInstructor()
				<< endl;
		}
	}

	void findBySubject(string& subj) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			transform(subj.begin(), subj.end(), subj.begin(), ::toupper);
			if (subj == item.getSubject()) {
				item.print();
			}
		}
	}
	void findBySubjectAndCatalog(string& subj, string& cat) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			transform(subj.begin(), subj.end(), subj.begin(), ::toupper);
			if (subj == item.getSubject() && cat == item.getCatalog()) {
				item.print();
			}
		}
	}

	void findByInstructor(string& lastName) {
		for (const auto& kvp : scheduleMap) {
			const scheduleItem& item = kvp.second;
			string instructorFullName = item.getInstructor();
			size_t comma = instructorFullName.find(',');
			string instructorLast;
			if (comma != string::npos) {
				instructorLast = instructorFullName.substr(0,comma);
			}
			else {
				instructorLast = instructorFullName;
			}
			if (capitalizeFirstLetter(lastName) == instructorLast) {
				item.print();
			}
		}
	}

	// Function in order for all cases for last name to be recognized
	string capitalizeFirstLetter(string input) {
		if (!input.empty()) {
			input[0] = toupper(input[0]);
			for (size_t i = 1; i < input.length(); ++i) {
				input[i] = tolower(input[i]);
			}
		}
		return input;
	}

};
