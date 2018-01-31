#ifndef SICT_DATE_H
#define SICT_DATE_H

#include <iostream>
#define min_year 2000
#define  max_year 2030



namespace sict {

	class Date {

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR  3
#define DAY_ERROR 4

		int d_year;
		int d_month;
		int d_day;
		int comp_value;
		int error_state;
		int mdays(int, int) const;
		void errCode(int errorCode);
		void isValid();

	public:
		void setEmpty();
		Date();
		Date(int year, int month, int day);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
	std::ostream& operator <<(std::ostream& os, const Date& A);
	std::istream& operator >>(std::istream& is, Date& A);

}
#endif
