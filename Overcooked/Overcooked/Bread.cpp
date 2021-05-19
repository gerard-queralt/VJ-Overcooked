#include "Bread.h"

bool Bread::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/Bread.obj", program);
}

string Bread::whatAmI()
{
	return "Bread";
}
