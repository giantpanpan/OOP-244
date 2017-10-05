#include "ArrayList.h"
#include<iostream>

using namespace std;
using namespace collection;

int main() 
{
	ArrayList al,a12;
	al.display();
	al.add(10);
	al.add(11);
	al.add(12);
	(al += 25) += 30; // to do this way, al must return itself, using "ArrayList& operator+=(short item);"
	al.display();
	(a12 += 100) += 200;
	al += a12; //using "ArrayList& operator+=(const ArrayList& aList);"
	al.display();
	if (al) //using "operator bool() const;" cast operator
	{
		cout << "not empty" << endl;
	}
	else {
		cout << "empty!" << endl;
	}
	ArrayList a14 = 50; //promoting 50 to a14, using "ArrayList(short item);"
	a14.display();
}