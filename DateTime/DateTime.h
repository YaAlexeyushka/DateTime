#include <iostream>

#ifndef DATETIME_H
#define DATETIME_H

using namespace std;

class DateTime {

public:
	int day, month, year, hour, minute, second;
	double julian_date;

	DateTime();
	DateTime(int _day, int _month, int _year);
	DateTime(int _day, int _month, int _year, int _hour, int _minute, int _second);

	double toJulian() const;
	DateTime toGregorian(double julian);
	bool isDateValid();
	bool check_leap_year() const;
	int dayOfWeek() const;

	friend ostream& operator <<(ostream& out, const DateTime& d);
	friend istream& operator >>(istream& in, DateTime& r);

	DateTime& operator -(const int& d);
	int& operator -(const DateTime& d);
};

#endif