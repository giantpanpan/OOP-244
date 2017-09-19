#include "engine.h"
using namespace racing;

int main() {
	Engine theEngine;
	theEngine.setEmpty();
	theEngine.set("LS1", 567);
	theEngine.display();
	Engine anotherEngine;
	anotherEngine.setEmpty();
	anotherEngine.display();
}