#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <string>
#include <iterator>
#include <utility>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "scheduleItem.h"
#include "HashTable.h"
using namespace std;

class schedule : public scheduleItem
{
private:
	HashTable<string, scheduleItem> scheduleTable;
public:
	schedule() {};
	schedule(int initialSize) : scheduleTable(initialSize) {};

	void setHashFunction(std::function<size_t(const std::string&)> hashFunc) {
		scheduleTable.setHashFunction(hashFunc);
	};

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

			// string to int
			int unitsStr = stoi(units);
			int totEnrlStr = stoi(totEnrl);
			int capEnrlStr = stoi(capEnrl);

			string key = subject + "_" + catalog + "_" + section; // AAA_101_D01F
			scheduleItem item(subject, catalog, section, component, session, unitsStr, totEnrlStr, capEnrlStr, instructor);
			scheduleTable.insert(key, item);
		}
		inFile.close();
	}

	void statistics() {
		cout << "Size of the hash table: " << scheduleTable.getSize() << endl;
		cout << "Number of buckets in hash table: " << scheduleTable.getBuckets() << endl;
		cout << "Load factor of the hash table: " << scheduleTable.getLoadFactor() << endl;
		cout << "Number of collisions: " << scheduleTable.countCollisions() << endl;
		cout << "Length of the longest chain: " << scheduleTable.maxBucketSize() << endl;
	}

	void printHeader() const {
		cout << "Subject " << " Catalog " << " Section " << " Component " << " Session " << " Units " << " TotEnrl " << " CapEnrl " << " Instructor " << endl;
	}

	void print() {
		for (size_t i = 0; i < scheduleTable.getBuckets(); ++i) {
			vector<scheduleItem> items = scheduleTable.getByIndex(i);
			for (const auto& item : items) {
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
	}

	void findBySubject(string& subj) {
		transform(subj.begin(), subj.end(), subj.begin(), ::toupper);
		for (size_t i = 0; i < scheduleTable.getBuckets(); ++i) {
			vector<scheduleItem> items = scheduleTable.getByIndex(i);
			for (const auto& item : items) {
				if (subj == item.getSubject()) {
					item.print();
				}
			}
		}
	}

	void findBySubjectAndCatalog(string& subj, string& cat) {
		transform(subj.begin(), subj.end(), subj.begin(), ::toupper);
		for (size_t i = 0; i < scheduleTable.getBuckets(); ++i) {
			vector<scheduleItem> items = scheduleTable.getByIndex(i);
			for (const auto& item : items) {
				if (subj == item.getSubject() && cat == item.getCatalog()) {
					item.print();
				}
			}
		}
	}

	void findByInstructor(string& lastName) {
		for (size_t i = 0; i < scheduleTable.getBuckets(); ++i) {
			vector<scheduleItem> items = scheduleTable.getByIndex(i);
			for (const auto& item : items) {
				string instructorFullName = item.getInstructor();
				size_t comma = instructorFullName.find(',');
				string instructorLast;
				if (comma != string::npos) {
					instructorLast = instructorFullName.substr(0, comma);
				}
				else {
					instructorLast = instructorFullName;
				}
				if (capitalizeFirstLetter(lastName) == instructorLast) {
					item.print();
				}
			}
		}
	}

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

#endif