#include "Onion.h"

bool Onion::init(ShaderProgram & program)
{
	setScale(2.f);
	return loadFromFile("models/onion.obj", program);
}
