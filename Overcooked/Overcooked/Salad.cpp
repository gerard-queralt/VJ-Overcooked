#include "Salad.h"

bool Salad::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/Salad.obj", program);
}

string Salad::whatAmI()
{
	return "Salad";
}
