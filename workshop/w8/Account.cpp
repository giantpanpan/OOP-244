// OOP244 Workshop 8: Virtual Functions and Abstract Base Classes
// File: Account.cpp
// Version: 2.0
// Date: 2017/12/11
// Author: Chris Szalwinski, based on previous work by Heidar Davoudi
// Description:
// This file implements the Account class
///////////////////////////////////////////////////

#include "Account.h"

namespace sict
{
	Account::Account(double amount)
	{
		if (amount > 0)
		{
			this->m_balance = amount;
		}
		else
		{
			this->m_balance = 0.0;
		}
	}

	bool Account::credit(double credit)
	{
		if (credit > 0)
		{
			this->m_balance += credit;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Account::debit(double debit)
	{
		if (debit > 0)
		{
			this->m_balance -= debit;
			return true;
		}
		else
		{
			return false;
		}
	}
	double Account::balance() const
	{
		return this->m_balance;
	}
}