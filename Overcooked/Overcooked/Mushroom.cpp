#include "Mushroom.h"

bool Mushroom::init(ShaderProgram & program)
{
	setScale(.25f);
	return loadFromFile("models/Mushroom.obj", program);
}

void Mushroom::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/MushroomCutted.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Mushroom::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Mushroom::isCut()
{
	return cutBool;
}

string Mushroom::whatAmI()
{
	return "Mushroom";
}
