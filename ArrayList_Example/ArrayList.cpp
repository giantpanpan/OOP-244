#include<iostream>
#include "ArrayList.h"

using namespace std;
namespace collection 
{
	ArrayList::ArrayList()
	{
		this->m_pItems = nullptr;
		this->m_size = 0;
	}
	ArrayList::~ArrayList() 
	{
		delete[] this->m_pItems;
		this->m_pItems = nullptr;
	}
	void ArrayList::add(short item) 
	{
		short* temp = new short[this->m_size + 1];
		for (int i = 0; i < this->m_size; i++) 
		{
			temp[i] = this->m_pItems[i];
		}
		delete[] this->m_pItems; // why we need to delete dynymic memory for current object here
		temp[this->m_size] = item;
		this->m_pItems = temp;
		this->m_size++;
	}

	void ArrayList::display() const {
		for (int i = 0; i < this->m_size; i++) {
			cout << " " << this->m_pItems[i]; 
		}
		cout << endl;
	}
	ArrayList& ArrayList::operator+=(const short item)
	{
		this->add(item);
		return *this;
	}
	ArrayList& ArrayList::operator+=(const ArrayList& alist)
	{
		for (int i=0;i<alist.m_size;i++)
		{
			this->add(alist.m_pItems[i]);
		}
		return *this;
	}
	ArrayList::operator bool() const {
		return this->m_size > 0;
	}
	ArrayList::ArrayList(short item)
	{
		*this = ArrayList();
		this->add(item);
	}
}