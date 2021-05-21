#include "Cheese.h"

bool Cheese::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/Cheese.obj", program);
}

void Cheese::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/CutCheese.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Cheese::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Cheese::isCut()
{
	return cutBool;
}

string Cheese::whatAmI()
{
	return "Cheese";
}
