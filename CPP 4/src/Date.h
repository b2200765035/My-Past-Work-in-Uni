#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;  

public:
	//constructors
	Date() {
			day = month = year = 0;
		}
	Date(string date) {
		char** next{};
		char cdate[11];
		strcpy_s(cdate, date.c_str());
		string idate[3];
		int i = 0;
		char* token = strtok_s(cdate, "-", next);
		while (token != NULL) {
			idate[i] = token;
			i++;
			token = strtok_s(NULL, "-", next);
		}
		this->day = stoi(idate[0]);
		this->month = stoi(idate[1]);
		this->year = stoi(idate[2]);
		}

	//getters
	string getDate() {
			string ds = to_string(day);
			string ms = to_string(month);
			string ys = to_string(year);
			return ds + '-' + ms + '-' + ys;
		}
	int getDay() const{
			return day;
		}
	int getMonth() const{
			return month;
		}
	int getYear() const{
			return year;
		}

	//overloading operators
	bool operator <(Date d) const {
			if (year < d.getYear()) {
				return true;
			}
			if (year == d.getYear() && month < d.getMonth()) {
				return true;
			}
			if (year == d.getYear() && month == d.getMonth() && day < d.getDay()) {
				return true;
			}
			return false;
		}

	bool operator >(Date d) const {
			if (year > d.getYear()) {
				return true;
			}
			if (year == d.getYear() && month > d.getMonth()) {
				return true;
			}
			if (year == d.getYear() && month == d.getMonth() && day > d.getDay()) {
				return true;
			}
			return false;
		}

	bool operator <=(Date d) const {
			if (year <= d.getYear()) {
				return true;
			}
			if (year == d.getYear() && month <= d.getMonth()) {
				return true;
			}
			if (year == d.getYear() && month == d.getMonth() && day <= d.getDay()) {
				return true;
			}
			return false;
		}

	bool operator >=(Date d) {
			if (year >= d.getYear()) {
				return true;
			}
			if (year == d.getYear() && month >= d.getMonth()) {
				return true;
			}
			if (year == d.getYear() && month == d.getMonth() && day >= d.getDay()) {
				return true;
			}
			return false;
		}

	bool operator ==(Date d) {
			if (year == d.getYear() && month == d.getMonth() && day == d.getDay()) {
				return true;
			}
			return false;
		}

	bool operator !=(Date d) {
			if (year == d.getYear() && month == d.getMonth() && day == d.getDay()) {
				return false;
			}
			return true;
		}

	friend ostream& operator<<(ostream& output, Date d) {
		string ds = to_string(d.getDay());
		string ms = to_string(d.getMonth());
		string ys = to_string(d.getYear());
		output << ds << '-' << ms << '-' << ys;
	}
};

