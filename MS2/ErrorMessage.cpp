// Final Project Milestone 2
// Version 1.0
// Date	
// Author	
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

namespace sict 
{
	ErrorMessage::ErrorMessage(const char* errorMessage = nullptr)
	{
		if (errorMessage == nullptr) 
		{
			delete [] m_ErrMessage;
			this->m_ErrMessage = new char[1];
			this->m_ErrMessage[0] = '\0';
		}
		else
		{
			delete [] m_ErrMessage;
			this->m_ErrMessage = new char[strlen(errorMessage) + 1];
			for (int i = 0; i < (strlen(errorMessage) + 1); i++) 
			{
				this->m_ErrMessage[i] = errorMessage[i];
			}
		}
	}

	ErrorMessage::~ErrorMessage()
	{
		delete [] this->m_ErrMessage;
		this->m_ErrMessage = nullptr;
	}

	void ErrorMessage::clear()
	{
		delete[] m_ErrMessage;
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
		delete [] m_ErrMessage;
		this->m_ErrMessage = new char[strlen(str) + 1];
		for (int i = 0; i < (strlen(str) + 1); i++)
		{
			this->m_ErrMessage[i] = str[i];
		}
	}

	const char* ErrorMessage::message()const 
	{
		return this->m_ErrMessage;
	}

	std::ostream& operator <<(std::ostream& os, const ErrorMessage& Err_Msg) 
	{
		if (!Err_Msg.isClear()) 
		{
			for (int i = 0; i < (strlen(Err_Msg.message()+1));i++)
			{
				os << Err_Msg.message()[i];
			}
			return os;
		}
	}


}