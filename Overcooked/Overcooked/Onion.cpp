#include "Onion.h"

bool Onion::init(ShaderProgram & program)
{
	setScale(.25f);
	return loadFromFile("models/Onion.obj", program);
}

void Onion::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/CutOnion.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Onion::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Onion::isCut()
{
	return cutBool;
}

string Onion::whatAmI()
{
	return "Onion";
}
