// OOP244 Workshop 8: Virtual Functions and Abstract Base Classes
// File: Allocator.cpp
// Version: 2.0
// Date: 2017/12/11
// Author: Chris Szalwinski, based on previous work by Heidar Davoudi
// Description:
// This file allocates an Account object in dynamic memory
///////////////////////////////////////////////////
#include "SavingsAccount.h" 
#include "ChequingAccount.h"

namespace sict {

	// define interest rate
	//
	const double interest_Rate = 0.05;
	const double transaction_fee = 0.50;
	const double monthly_fee = 2.00;


	// TODO: Allocator function
	//
	iAccount* CreateAccount(const char* account, double amount)
	{
		iAccount* customer = nullptr;
		if (account[0] == 'S')
		{
			customer = new SavingsAccount(amount, interest_Rate);
		}
		else if (account[0] =='C')
		{
			customer = new ChequingAccount(amount, transaction_fee, monthly_fee);
		}
		return customer;

	}








}
