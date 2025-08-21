// BBM203 Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CircularArrayLinkedList.h"
#include "DoubleLinkedDynamicList.h"
using namespace std;
int re;

int main()
{
	int ID = 0;
	int permanancy = 0;
	string name;
	string surname;
	string title;
	double salaryCoefficent = 0.0;
	string sbirth;
	Date birth;
	string sappointment;
	Date appointment;
	int service = 0;

	CircularArrayLinkedList CALL;
	DoubleLinkedDynamicList DLDL;
	DoubleLinkedDynamicList::NODEPTR head = NULL;


	int choice;
	bool program = true;
	while (program != false) {
		cout << "___________Employee Recording System___________" << endl
			<< " 1 - Appointment of a new employee" << endl
			<< " 2 - Appointment of a transferred employee" << endl
			<< " 3 - Updating title and the salary coefficent of an employee" << endl
			<< " 4 - Deletion of an employee" << endl
			<< " 5 - Listing the information of an employee" << endl
			<< " 6 - Listing employees ordered by employee number" << endl
			<< " 7 - Listing employees ordered by appointment date" << endl
			<< " 8 - Listing employees appointed after a certain date" << endl
			<< " 9 - Listing employees assigned in a given year" << endl
			<< " 10 - Listing employees born before a certain date" << endl
			<< " 11 - Listing employees born in a particular month" << endl
			<< " 12 - Listing the information of the last assigned employee with a given title" << endl
			<< " 13 - Exit" << endl
			<< "___________Employee Recording System___________" << endl;

		cin >> choice;

		switch (choice)
		{
			case 1:
				cout << "Please type the employee ID:" << endl;
				cin >> ID;
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				re = DLDL.search(&head, ID);
				if (re != -1) {
					cout << "The employee with that ID number exists" << endl;
					break;
				}
				else {
					cout << "Please type the employee type" << endl;
					cin >> permanancy;
					cout << "Please type the employee's name" << endl;
					getline(cin, name);
					cout << "Please type the employee's surname" << endl;
					getline(cin, surname);
					cout << "Please type the employee's title" << endl;
					getline(cin, title);
					cout << "Please type the employee's salary coefficent" << endl;
					cin >> salaryCoefficent;
					cout << "Please type the employee's birthdate" << endl;
					cin >> sbirth;
					cout << "Please type the employee's apoointment date" << endl;
					cin >> sappointment;
					service = 0;
					birth = Date(sbirth);
					appointment = Date(sappointment);
					if (permanancy == 0) {
						CALL.addTEmployee(TemporaryEmployee(ID, name, surname, title, salaryCoefficent, birth, appointment, service));
						cout << "Temporary employee succsessfully added" << endl;
					}
					else {
						DLDL.insertfront(head, PermanentEmployee(ID, name, surname, title, salaryCoefficent, birth, appointment, service));
						cout << "Permanent employee succsessfully added" << endl;
					}
				}
				DLDL.deleteTemp(&head);
				break;
			case 2:
				cout << "Please type the employee ID:" << endl;
				cin >> ID;
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				re = DLDL.search(&head, ID);
				if (re != -1) {
					cout << "The employee with that ID number exists" << endl;
					break;
				}
				else {
					cout << "Please type the employee type" << endl;
					cin >> permanancy;
					cout << "Please type the employee's name" << endl;
					getline(cin, name);
					cout << "Please type the employee's surname" << endl;
					getline(cin, surname);
					cout << "Please type the employee's title" << endl;
					getline(cin, title);
					cout << "Please type the employee's salary coefficent" << endl;
					cin >> salaryCoefficent;
					cout << "Please type the employee's birthdate" << endl;
					cin >> sbirth;
					cout << "Please type the employee's apoointment date" << endl;
					cin >> sappointment;
					cout << "Please type the employee's previous service days" << endl;
					cin >> service;
					birth = Date(sbirth);
					appointment = Date(sappointment);
					if (permanancy == 0) {
						CALL.addTEmployee(TemporaryEmployee(ID, name, surname, title, salaryCoefficent, birth, appointment, service));
						cout << "Temporary employee succsessfully added" << endl;
					}
					else {
						DLDL.insertfront(head, PermanentEmployee(ID, name, surname, title, salaryCoefficent, birth, appointment, service));
						cout << "Permanent employee succsessfully added" << endl;
					}
				}
				break;
				break;
			case 3:
				cout << "Please type the employee ID:" << endl;
				cin >> ID;
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i]->getID() == ID) {
						cout << "Please type the new title:" << endl;
						getline(cin, title);
						CALL.Carray[i]->setTitle(title);
						cout << "Please type the new salary coefficent:" << endl;
						cin >> salaryCoefficent;
						CALL.Carray[i]->setSalaryCoefficent(salaryCoefficent);
						cout << "Title and salary coefficent updated" << endl;
						break;
					}
				}
				re = DLDL.search(&head, ID);
				if (re != -1) {
					DoubleLinkedDynamicList::NODEPTR temp = DLDL.deleteID(&head, ID);
					cout << "Please type the new title:" << endl;
					getline(cin, title);
					temp->employee->setTitle(title);
					cout << "Please type the new salary coefficent:" << endl;
					cin >> salaryCoefficent;
					temp->employee->setSalaryCoefficent(salaryCoefficent);
					cout << "Title and salary coefficent updated" << endl;
					DLDL.insertfront(head, *temp->employee);
					break;
				}
				cout << "There is no employee with that ID" << endl;
				break;
			case 4:
				cout << "Please type the employee ID:" << endl;
				cin >> ID;
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i]->getID() == ID) {
						CALL.deleteTemployee(ID);
						cout << "Temporary employee deleted" << endl;
						break;
					}
				}
				re = DLDL.search(&head, ID);
				if (re != -1) {
					DLDL.deleteID(&head, ID);
					cout << "Permanent employee deleted" << endl;
				}
				cout << "There is no employee with that ID" << endl;
				break;
			case 5:
				cout << "Please type the employee ID:" << endl;
				cin >> ID;
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				re = DLDL.search(&head, ID);
				if (re != -1) {
					DoubleLinkedDynamicList::NODEPTR temp = DLDL.deleteID(&head, ID);
					cout << temp->employee;
					DLDL.insertfront(head, *temp->employee);
				}
				else {
					cout << "There is no employee with that ID number" << endl;
				}
				DLDL.deleteTemp(&head);
				break;
			case 6:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				DLDL.IDsort(head);
				DLDL.displayList(head);
				DLDL.deleteTemp(&head);
				break;
			case 7:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				DLDL.Appointsortntoo(head);
				DLDL.displayList(head);
				DLDL.deleteTemp(&head);
				break;
			case 8:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				cout << "Please write the desired appointment date:" << endl;
				cin >> sappointment;
				appointment = Date(sappointment);
				DLDL.IDsort(head);
				DLDL.displayAppoint(head, appointment);
				DLDL.deleteTemp(&head);
				break;
			case 9:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				cout << "Please write the desired appointment year:" << endl;
				int year;
				cin >> year;
				DLDL.IDsort(head);
				DLDL.displayYear(head, year);
				DLDL.deleteTemp(&head);
				break;
			case 10:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				cout << "Please write the desired brith date:" << endl;
				cin >> sbirth;
				birth = Date(sbirth);
				DLDL.IDsort(head);
				DLDL.displayAppoint(head, birth);
				DLDL.deleteTemp(&head);
				break;
			case 11:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				cout << "Please write the desired birth month:" << endl;
				int month;
				cin >> month;
				DLDL.IDsort(head);
				DLDL.displayMonth(head, month);
				DLDL.deleteTemp(&head);
				break;
			case 12:
				for (int i = 0; i < 20; i++) {
					if (CALL.Carray[i] != NULL) {
						DLDL.insertfront(head, *CALL.Carray[i]);
					}
				}
				cout << "Please write the desired title:" << endl;
				getline(cin, title);
				DLDL.Appointsortoton(head);
				DoubleLinkedDynamicList::NODEPTR last;

				while (&head != NULL) {
					if (head->employee->getTitle() == title) {
						cout << &head->employee;
						break;
					}
					last = head;
					head = head->next;
				}
				if (&head == NULL) {
					cout << "NULL";
				}
				break;
			case 13:
				cout << "End of Program.\n";
				program = false;
				break;
			default:
				cout << "Not a Valid Choice. \n";
				cout << "Choose again.\n";
				cin >> choice;
				break;
		}

	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
