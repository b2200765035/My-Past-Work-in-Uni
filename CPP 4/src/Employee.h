#pragma once
#include <iostream>
#include <string>
#include "Date.h"
using namespace::std;

class Employee
{
private:
	int ID;
	bool permanancy;
	const string name;
	const string surname;
	string title;
	double salaryCoefficent;
	const Date birth;
	const Date appointment;
	int service;

public:
	//constructor
	Employee() {};
	Employee(int ID, string name, string surname, string title, double salaryCoefficent, Date birth, Date appointment, int service) :name(name), surname(surname), birth(birth), appointment(appointment)
		{
		this->ID = ID;
		this->title = title;
		this->salaryCoefficent = salaryCoefficent;
		this->service = service;
	}

	//getters and setters
	void setID(int ID) {
		this->ID = ID;
	}
	void setPermanancy(bool permanancy) {
		this->permanancy = permanancy;
	}
	void setTitle(string title) {
		this->title = title;
	}
	void setSalaryCoefficent(double salaryCoefficent) {
		this->salaryCoefficent = salaryCoefficent;
	}
	void setService(int Service) {
		this->service = service;
	}

	int getID() {
		return ID;
	}
	bool getPermanancy() {
		return permanancy;
	}
	string getName() {
		return name;
	}
	string getSurname() {
		return surname;
	}
	string getTitle() {
		return title;
	}
	double getSalaryCoefficent() {
		return salaryCoefficent;
	}
	Date getBirth() {
		return birth;
	}
	int getBrithMonth() {
		int month = birth.getMonth();
		return month;
	}
	Date getAppointment() {
		return appointment;
	}
	int getAppointYear() {
		int year = appointment.getYear();
		return year;
	}
	int getService() {
		return service;
	}


	//overloading <<
	friend ostream& operator<<(ostream& output, Employee e) {
		if (e.getPermanancy() == false) {
			output << "ID of this employee: " << to_string(e.getID()) << endl
				<< "This employee is temporary" << endl
				<< "Name of this employee: " << e.getName() << endl
				<< "Surname of this employee: " << e.getName() << endl
				<< "Title of this employee: " << e.getName() << endl
				<< "SalaryCoefficent of this employee: " << e.getName() << endl
				<< "Birth date of this employee: " << e.getName() << endl
				<< "Appointment date of this employee: " << e.getName() << endl
				<< "How long this employee has worked for before: " << e.getName() << " days."
				<< "-------------------------------" << endl;
		}
		else {
			output << "ID of this employee: " << to_string(e.getID()) << endl
				<< "This employee is permanent" << endl
				<< "Name of this employee: " << e.getName() << endl
				<< "Surname of this employee: " << e.getName() << endl
				<< "Title of this employee: " << e.getName() << endl
				<< "SalaryCoefficent of this employee: " << e.getName() << endl
				<< "Birth date of this employee: " << e.getName() << endl
				<< "Appointment date of this employee: " << e.getName() << endl
				<< "How long this employee has worked for before: " << e.getName() << " days."
				<< "-------------------------------" << endl;
		}
		
	}
};

