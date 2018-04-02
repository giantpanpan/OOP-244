// OOP244 Workshop 8: Virtual Functions and Abstract Base Classes
// File: SavingsAccount.cpp
// Version: 2.0
// Date: 2017/12/11
// Author: Chris Szalwinski, based on previous work by Heidar Davoudi
// Description:
// This file implements the SavingsAccount class
///////////////////////////////////////////////////

#include <iostream>
#include "SavingsAccount.h"

namespace sict
{
	SavingsAccount::SavingsAccount(double init_balance, double inst_rate) : Account(init_balance)
	{
		if (inst_rate > 0)
		{
			this->interest_Rate = inst_rate;
		}
		else
		{
			this->interest_Rate = 0.0;
		}
	}
	void SavingsAccount::monthEnd()
	{
		double interest;
		interest = this->interest_Rate*this->balance();
		this->credit(interest);
	}

	void SavingsAccount::display(std::ostream& os) const
	{
		os.setf(std::ios::fixed);
		os.precision(2);
		os << "Account type: Savings" << std::endl;
		os << "Balance: $" << this->balance() << std::endl;
		os << "Interest Rate (%): " << this->interest_Rate * 100 << std::endl;
	}
}
