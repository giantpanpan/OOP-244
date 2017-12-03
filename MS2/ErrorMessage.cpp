// Final Project Milestone 2
// Version 1.0
// Date	
// Author	
//
// Revision History
// -----------------------------------------------------------
// Name              Date                 Reason
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"



namespace sict
{
	ErrorMessage::ErrorMessage(const char* errorMessage) //don't need to redefine the default parameter if it
														 // is already define in the function decalaration
	{
		if (nullptr == errorMessage)
		{ 
			//delete[] m_ErrMessage;                    // in g++ compiler, we cannot delete the already deleted memory. 
			this->m_ErrMessage = new char[1];
			this->m_ErrMessage[0] = '\0';
		}
		else
		{
			//delete[] m_ErrMessage;
			this->m_ErrMessage = new char[strlen(errorMessage)+1];
			strcpy(this->m_ErrMessage, errorMessage);
			//this->m_ErrMessage[strlen(errorMessage)] = '\0';
		}
	}

	ErrorMessage::~ErrorMessage()
	{
		delete[] this->m_ErrMessage;
		this->m_ErrMessage = nullptr;
	}

	void ErrorMessage::clear()
	{
		//delete[] m_ErrMessage;
		this->m_ErrMessage = new char[1];
		this->m_ErrMessage[0] = '\0';
	}

	bool ErrorMessage::isClear() const
	{
		if (this->m_ErrMessage[0] == '\0')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ErrorMessage::message(const char* str)
	{
		delete [] this->m_ErrMessage;
		this->m_ErrMessage = new char[strlen(str) + 1];
		strcpy(this->m_ErrMessage, str);
		this->m_ErrMessage[strlen(str)] = '\0';                            //must clear the previous value stored in current object
	}

	const char* ErrorMessage::message()const
	{
		return this->m_ErrMessage;
	}

	std::ostream& operator <<(std::ostream& os, const ErrorMessage& Err_Msg)   //passed by the reference of an object and access the reference of char pointer and display value
		                                                                       // the left hand operand should be a inference. 
	{
		if (!Err_Msg.isClear())
		{
			os << Err_Msg.message()<< '\0';
			return os;
		}
		else
		{
			return os;
		}
	}


}
