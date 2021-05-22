#include "Extinguisher.h"

bool Extinguisher::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/Extinguisher.obj", program);
}

string Extinguisher::whatAmI()
{
	return "Extinguisher";
}
