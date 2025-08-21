#pragma once
#include "Employee.h"
class TemporaryEmployee :
    public Employee
{
public:
	TemporaryEmployee() {};
	TemporaryEmployee(int ID, string name, string surname, string title, double salaryCoefficent, Date birth, Date appointment, int service):
		Employee(ID, name, surname, title, salaryCoefficent, birth, appointment, service)
	{
		setPermanancy(false);
	}

	friend ostream& operator<<(ostream& output, TemporaryEmployee e) {
		output << "ID of this employee: " << to_string(e.getID()) << endl
			<< "This employee is a temporary employee." << endl
			<< "Name of this employee: " << e.getName() << endl
			<< "Surname of this employee: " << e.getName() << endl
			<< "Title of this employee: " << e.getName() << endl
			<< "SalaryCoefficent of this employee: " << e.getName() << endl
			<< "Birth date of this employee: " << e.getName() << endl
			<< "Appointment date of this employee: " << e.getName() << endl
			<< "How long this employee has worked for before: " << e.getName() << " days."
			<< "-------------------------------" << endl;
	}
};

