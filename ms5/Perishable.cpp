#include <iostream>
#include "Perishable.h"

namespace sict
{
	Perishable::Perishable () : NonPerishable('P')
	{
		

	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		NonPerishable::store(file, false);
		file << ",";
		file << expire_date;
		if (newLine)
		{
			file << '\n';
		}
		else
		{
			file << ",";
		}
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		NonPerishable::load(file);
		this->expire_date.read(file);
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		NonPerishable::write(os, linear);
		if(this->name() != nullptr && this->isClear())
		{
			if (linear)
			{
				os << this->expire_date;
			}
			else
			{
				os << std::endl << "Expiry date: " << this->expire_date;
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		NonPerishable::read(is);
		if (!is.fail())
		{
			Date t_date;
			std::cout << "Expiry date (YYYY/MM/DD): ";
			is >> t_date;
			if (!is.fail()) 
			{
				if (t_date.bad())
				{
					if (t_date.errCode() == CIN_FAILED)
					{
						this->message("Invalid Date Entry");
						is.setstate(std::ios::failbit);
					}
					else if (t_date.errCode() == YEAR_ERROR)
					{
						this->message("Invalid Year in Date Entry");
						is.setstate(std::ios::failbit);
					}
					else if (t_date.errCode() == MON_ERROR)
					{
						this->message("Invalid Month in Date Entry");
						is.setstate(std::ios::failbit);
					}
					else if (t_date.errCode() == DAY_ERROR)
					{
						is.setstate(std::ios::failbit);
						this->message("Invalid Day in Date Entry");
					}
				}
				else
				{
					this->expire_date = t_date;
				}
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return this->expire_date;
	}

	Product* CreatePerishable()
	{
		Product* aPerishable = nullptr;
		aPerishable = new Perishable;
		return aPerishable;
	}
}
