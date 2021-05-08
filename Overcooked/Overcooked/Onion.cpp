#include "Onion.h"

bool Onion::init(ShaderProgram & program)
{
	return loadFromFile("models/onion.obj", program);
}
