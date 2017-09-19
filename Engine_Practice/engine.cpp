#include "engine.h"
#include<iostream>
#include<cstring>

using namespace std;
using namespace racing;

namespace racing
{
	void Engine::setEmpty()
	{
		m_pModel = nullptr;
		m_hp = 0;
	}
	void Engine::set(const char *pModel, short hp)
	{
		if (nullptr != m_pModel) {
			delete[] m_pModel;
		}
		int size = strlen(pModel);
		m_pModel = new char[size + 1];
		strcpy(m_pModel, pModel);
		m_hp = hp;

	}
	void Engine::display() const
	{
		if (nullptr != m_pModel && 0 != m_hp) {
			cout << m_pModel << endl;
			cout << m_hp << endl;
		}
		else {
			cout << "No engine set!" << endl;
		}
	}
}