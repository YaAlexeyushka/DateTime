#include <iostream>
#include <fstream>
#include "DateTime/DateTime.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru-RU");

	DateTime date(04, 05, 2020, 05, 02, 40);
	cout << date << endl;

	DateTime date2(11, 4, 2024);
	cout << date2.dayOfWeek() << endl;

	try {
		DateTime date3(40, 13, 2020);
	}
	catch (...) {
		cerr << "Date is invalid" << endl;
	}

	try {
		DateTime date4(15, 2, 2024);
		DateTime result;
		result = date4 - 15;
		cout << result << endl;
	}
	catch (...) {
		cerr << "Date is invalid" << endl;
	}

	try {
		DateTime date5;
		cout << "¬ведите дату: год мес€ц число или yyyy-MM-ddThh:mm:ss" << endl;
		cin >> date5;
		cout << date5 << endl;
	}
	catch (...) {
		cerr << "Date is invalid" << endl;
	}
}




