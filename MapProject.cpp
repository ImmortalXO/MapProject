#include <iostream>
#include <fstream>
#include "schedule.h"
using namespace std;

int showMenu() {
	int choice;
	cout << "Choose one of the menu items below:" << endl;
	cout << "1. Find By Subject" << endl;
	cout << "2. Find By Subject and Catalog" << endl;
	cout << "3. Find By Instructor's Last Name" << endl;
	cout << "4. Print All Records" << endl;
	cout << "5. Quit" << endl;
	cout << "Choice: ";
	cin >> choice;
	return choice;
}

int main() {
	ifstream dataFile("STEM - Summer 2022 Schedule of Classes as of 05-02-22(1).csv");
	schedule item;
	item.initSchedule(dataFile);

	string subject, catalog, lastName;
	int choice = showMenu();
	switch (choice) {
		case 1:
			cout << "Enter the name of the subject: ";
			cin >> subject;
			item.printHeader();
			item.findBySubject(subject);
			break;
		case 2: 
			cout << "Enter the name of the subject: ";
			cin >> subject;
			cout << "Enter the name of the catalog: ";
			cin >> catalog;
			item.printHeader();
			item.findBySubjectAndCatalog(subject, catalog);
			break;
		case 3:
			cout << "Enter the last name of the instructor: ";
			cin >> lastName;
			item.printHeader();
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
	return 0;
}