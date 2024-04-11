#include "DateTime.h"
#include <iostream>
#include <sstream>

using namespace std;

DateTime::DateTime() {

	day = 0;
	month = 0;
	year = 0;
	hour = 0;
	minute = 0;
	second = 0;

	julian_date = toJulian();

}

DateTime::DateTime(int _day, int _month, int _year) {
	day = _day;
	month = _month;
	year = _year;
	hour = 0;
	minute = 0;
	second = 0;

	julian_date = toJulian();

	if (!isDateValid()) {
		throw "Date is invalid";
	}
}

DateTime::DateTime(int _day, int _month, int _year, int _hour, int _minute, int _second) {
	day = _day;
	month = _month;
	year = _year;
	hour = _hour;
	minute = _minute;
	second = _second;

	julian_date = toJulian();
	if (!isDateValid()) {
		throw "Date in invalid!";
	}
}

ostream& operator <<(ostream& out, const DateTime& d) {
	out << d.year << "." << d.month << "." << d.day << " " 
		<< d.hour << ":" << d.minute << ":" << d.second;
	return out;
}

istream& operator >>(istream& in, DateTime& d) {
	char separator[5];
	string tempIn;

	getline(in, tempIn);
	istringstream iss(tempIn);
	
	if (tempIn.find('T') != string::npos) {
		iss >> d.year >> separator[0] >> d.month >> separator[1] >> d.day
			>> separator[2] >> d.hour >> separator[3] >> d.minute >> separator[4] >> d.second;

		if (separator[0] != '-' or separator[1] != '-' or separator[2] != 'T'
			or separator[3] != ':' or separator[4] != ':') {
			throw "Date is invalid";
		}
	}

	else {
		iss >> d.year >> separator[0] >> d.month >> separator[1] >> d.day;
	}

	if (!d.isDateValid()) {
		throw "Date is invalid";
	}

	d.julian_date = d.toJulian();

	return in;
}

DateTime& DateTime::operator -(const int& d) {
	DateTime temp(*this), result;
	temp.julian_date -= d;
	result = toGregorian(temp.julian_date);

	return result;
}

int& DateTime::operator -(const DateTime& d) {
	int result;
	result = abs(julian_date - d.julian_date);

	return result;
}

int DateTime::dayOfWeek() const {
	return (int(toJulian() + 1.5) % 7);
}

double DateTime::toJulian() const {
	DateTime temp(*this);
	double days;
	int A = int(temp.year / 100);
	int B = 2 - A + int(A / 4);
	if (temp.month == 1 or temp.month == 2) {
		temp.year = temp.year - 1;
		temp.month = temp.month + 12;
	}
	days = int(365.25 * (temp.year + 4716)) + int(30.6001 * (temp.month + 1)) + temp.day + B - 1524.5;
	return days;
}

DateTime DateTime::toGregorian(double julian) {
	julian += 0.5;
	int z = int(julian);
	double F = julian - int(julian);
	int A, alpha, B, C, D, E;

	DateTime result;
	if (z < 2299161) {
		A = z;
	}
	else {
		alpha = int((z - 1867216.25) / 36524.25);
		A = z + 1 + alpha - int(alpha / 4);
	}
	B = A + 1524;
	C = int((B - 122.1) / 365.25);
	D = int((365.25) * C);
	E = int((B - D) / 30.6001);

	result.day = int(B - D - int(30.6001 * E) + F);
	if (E < 14) {
		result.month = E - 1;
	}
	else if (E == 14 or E == 15) {
		result.month = E - 13;
	}
	if (result.month > 2) {
		result.year = C - 4716;
	}
	else if (result.month == 1 or result.month == 2) {
		result.year = C - 4715;
	}
	result.julian_date = result.toJulian();

	return result;
}

bool DateTime::check_leap_year() const {
	if ((year % 4 == 0 and year % 100 != 0) or year % 400 == 0) {
		return true;
	} return false;
}

bool DateTime::isDateValid() {
	if (month < 1 or month > 12) {
		return false;
	}

	if (day < 1) {
		return false;
	}
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (check_leap_year()) {
		daysInMonth[1] = 29;
	}
	if (day > daysInMonth[month - 1]) {
		return false;
	}

	return true;
}

