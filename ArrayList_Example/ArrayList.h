#ifndef COLLECTION_ARRAYLIST_H
#define COLLECTION_ARRAYLIST_H

namespace collection
{
	class ArrayList
	{
		short* m_pItems;
		// the number of items in m_pItems
		int m_size;
	public:
		ArrayList();
		~ArrayList();
		void display() const;
		void add(short item);
		ArrayList& operator+=(short item); //copy assignment operator
		ArrayList& operator+=(const ArrayList& aList); //copy assignment operator
		operator bool() const; //cast operator
		ArrayList(short item); //promiting constructor
	};
}

#endif