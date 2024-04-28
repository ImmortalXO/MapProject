#include <iostream>
#include <fstream>
#include "schedule.h"
using namespace std;
int main() {
	ifstream dataFile("STEM - Summer 2022 Schedule of Classes as of 05-02-22(1).csv");
	schedule item;
	item.initSchedule(dataFile);

	int choice;
	string subject, catalog, lastName;

	while (choice != 5) {
		cout << "Choose one of the menu items below:" << endl;
		cout << "1. Find By Subject" << endl;
		cout << "2. Find By Subject and Catalog" << endl;
		cout << "3. Find By Instructor's Last Name" << endl;
		cout << "4. Print All Records" << endl;
		cout << "5. Quit" << endl;
		switch (choice) {
			case 1:
				cout << "Enter the name of the subject: ";
				cin >> subject;
				item.findBySubject(subject);
				break;
			case 2: 
				cout << "Enter the name of the subject: ";
				cin >> subject;
				cout << "Enter the name of the catalog: ";
				cin >> catalog;
				item.findBySubjectAndCatalog(subject, catalog);
				break;
			case 3:
				cout << "Enter the last name of the instructor: ";
				cin >> lastName;
				item.findByInstructor(lastName);
				break;
			case 4:
				item.printHeader();
				item.print();
				break;
			case 5:
				cout << "Goodbye.";
				break;
		}
	}

	return 0;
}