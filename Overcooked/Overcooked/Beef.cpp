#include "Beef.h"

bool Beef::init(ShaderProgram & program)
{
	setScale(.25f);
	return loadFromFile("models/Beef.obj", program);
}

void Beef::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/RawBurger.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Beef::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Beef::isCut()
{
	return cutBool;
}

string Beef::whatAmI()
{
	return "Beef";
}
