// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name  Wang Pan            Date  2017/11/20             Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"



namespace sict {
	void Date::setEmpty()
	{
		this->d_day = 00;
		this->d_month = 00;
		this->d_year = 0000;
	}
	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::isValid()
	{
		if (this->d_year < min_year || this->d_year > max_year)
		{
			this->error_state = YEAR_ERROR;
			//setEmpty();
		}
		else if (this->d_month <1 || this->d_month>12)
		{
			this->error_state = MON_ERROR;
			//setEmpty();
		}
		else if (this->d_day <1 || this->d_day > mdays(this->d_month, this->d_year))
		{
			this->error_state = DAY_ERROR;
			//setEmpty();
		}
		else
		{
			this->error_state = NO_ERROR;
		}
	}
	void Date::errCode(int errorCode)
	{
		if (errorCode == 0) 
		{
			this->error_state = NO_ERROR;
		}
		else if (errorCode == 1)
		{
			this->error_state = CIN_FAILED;
		}
		else if(errorCode ==2)
		{
			this->error_state = YEAR_ERROR;
		}
		else if(errorCode ==3)
		{
			this->error_state = MON_ERROR;
		}
		else if(errorCode ==4)
		{
			this->error_state = DAY_ERROR;
		}
		else
		{
			this->error_state = -1;
		}
		
	}

	Date::Date()
	{
		setEmpty();
		this->errCode(0);
		this->comp_value = 0;
	}

	Date::Date(int year, int month, int day)
	{
		if ((year>min_year && year <max_year) && (month>0 && month<13))
		{
			this->d_year = year;
			this->d_month = month;
			if (day <= this->mdays(month, year) && day >0)
			{
				this->d_day = day;
			}
			this->comp_value = this->d_year * 372 + this->d_month * 13 + this->d_day;
			this->errCode(0);
		}
		else
		{
			*this = Date();
		}
	}

	bool Date::operator==(const Date& rhs) const
	{
		if (this->comp_value!=0 && rhs.comp_value!=0)
		{
			return this->comp_value == rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator!=(const Date& rhs) const
	{
		if (this->comp_value != 0 && rhs.comp_value != 0)
		{
			return this->comp_value != rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<(const Date& rhs) const
	{
		if (this->comp_value != 0 && rhs.comp_value != 0)
		{
			return this->comp_value < rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>(const Date& rhs) const
	{
		if (this->comp_value != 0 && rhs.comp_value != 0)
		{
			return this->comp_value > rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<=(const Date& rhs) const
	{
		if (this->comp_value != 0 && rhs.comp_value != 0)
		{
			return this->comp_value <= rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>=(const Date& rhs) const
	{
		if (this->comp_value != 0 && rhs.comp_value != 0)
		{
			return this->comp_value >= rhs.comp_value;
		}
		else
		{
			return false;
		}
	}

	int Date::errCode() const
	{
		return this->error_state;
	}

	bool Date::bad() const
	{
		return this->error_state != NO_ERROR;
	}

	std::istream& Date::read(std::istream& istr)
	{
		istr >> this->d_year;
		if (istr.get() != '/')
		{
			this->error_state = CIN_FAILED;
			return istr;
		}
		istr >> this->d_month;
		if  (istr.get() != '/')
		{
			this->error_state = CIN_FAILED;
			return istr;
		}
		istr >> this->d_day;
		isValid();
		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr) const
	{
		ostr << this->d_year << '/';
		ostr.width(2);
		ostr.fill('0');
		ostr << this->d_month << '/';
		ostr.width(2);
		ostr << this->d_day;
		return ostr;
	}
	std::ostream& operator <<(std::ostream& os, const Date& A) 
	{
		A.write(os);
		return os;
	}
	std::istream& operator >>(std::istream& is, Date& A)
	{
		A.read(is);
		return is;
	}

}
