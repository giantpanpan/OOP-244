// OOP244 Workshop 8: Virtual Functions and Abstract Base Classes
// File: ChequingAccount.cpp
// Version: 2.0
// Date: 2017/12/11
// Author: Chris Szalwinski, based on previous work by Heidar Davoudi
// Description:
// This file implements the ChequingAccount class
///////////////////////////////////////////////////

#include <iostream>
#include "ChequingAccount.h"
#include "SavingsAccount.h"
using namespace std;

namespace sict {
	// constructor initializes balance and transaction fee
	//
	ChequingAccount::ChequingAccount(double init_balance, double trans_fee, double month_fee) :Account(init_balance)
	{
		if (trans_fee > 0) 
		{
			this->m_transactionFee = trans_fee;
		}
		else 
		{
			this->m_transactionFee = 0.0;
		}
		if (month_fee > 0) 
		{
			this->m_monthlyFee = month_fee;
		}
		else
		{
			this->m_monthlyFee = 0;
		}
	}


	// credit (add) an amount to the account balance and charge fee
	// returns bool indicating whether money was credited
	//

	bool ChequingAccount::credit(double amount)
	{
		if (amount > 0) 
		{
			Account::credit(amount);
			Account::debit(this->m_transactionFee);
			return true;
		}
		else
		{
			return false;
		}
	}


	// debit (subtract) an amount from the account balance and charge fee
	// returns bool indicating whether money was debited
	//
	bool ChequingAccount::debit(double amount)
	{
		if (amount > 0) 
		{
			Account::debit(amount);
			Account::debit(this->m_transactionFee);
			return true;
		}
		else
		{
			return false;
		}
	}


	// monthEnd debits month end fee
	//

	void ChequingAccount::monthEnd()
	{
		this->debit(this->m_monthlyFee);
	}

	// display inserts account information into ostream os
	//
	void ChequingAccount::display(std::ostream& os) const
	{
		os.setf(std::ios::fixed);
		os.precision(2);
		os << "Account type: Chequing" << std::endl;
		os << "Balance: $" << this->balance() << std::endl;
		os << "Per Transaction Fee: " << this->m_transactionFee << std::endl;
		os << "Monthly Fee: " << this->m_monthlyFee << std::endl;
	}



}
