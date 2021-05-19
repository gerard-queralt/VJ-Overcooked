#include "Burger.h"

bool Burger::init(ShaderProgram & program)
{
	setScale(.5f);
	this->program = program;
	return loadFromFile("models/BurgerBread.obj", program);
}

string Burger::whatAmI()
{
	return "Burger";
}
