#include "Onion.h"

bool Onion::init(ShaderProgram & program)
{
	setScale(2.f);
	return loadFromFile("models/onion.obj", program);
}

void Onion::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/onion_cut.obj", program);
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
