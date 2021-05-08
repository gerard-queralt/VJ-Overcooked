#include "FryingPan.h"

bool FryingPan::init(ShaderProgram & program)
{
	return loadFromFile("models/pan.obj", program);
}
