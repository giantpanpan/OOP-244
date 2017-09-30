#include<iostream>
#include"FireTruck.h"
using namespace std;
namespace safety {
	void Firetruck::setEmpty() 
	{
		m_pColor = nullptr;
		m_waterCap = 0;
	}

	void Firetruck::display()
	{
		if (nullptr != m_pColor) 
		{
			cout << "The color of the firetruck is: " << *m_pColor << endl;
			cout << "Water capacity is: " << m_waterCap << endl;
		}
	}

	Firetruck::Firetruck()
	{
		cout << "Firetruck::Firetruck()" << endl;
		setEmpty();
	}
	Firetruck::Firetruck(short cap, const char *pCal)
	{
		m_waterCap = cap;
		m_pColor = new char[strlen(pCal + 1)];
	}
	Firetruck::~Firetruck()
	{
		delete[] m_pColor;
		//m_pColor = nullptr;
	}
}