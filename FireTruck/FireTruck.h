#ifndef SAFETY_FIRETRUCK_H
#define SAFETY_FIRETRUCK_H

namespace safety 
{
	class Firetruck {
		char* m_pColor;
		short m_waterCap;
	public: 
		void setEmpty();
		void display();
		Firetruck();
		Firetruck(short cap, const char* pCol = "Red");
		~Firetruck();
	};
}

#endif