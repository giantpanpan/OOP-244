#include"FireTruck.h"
using namespace safety;

int main() 
{
	Firetruck aTruck;
	aTruck.display();
	Firetruck anotherTruck(10);
	anotherTruck.display();
	Firetruck thirdTruck(100, "pink");
}