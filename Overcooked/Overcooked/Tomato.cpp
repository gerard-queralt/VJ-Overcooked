#include "Tomato.h"

bool Tomato::init(ShaderProgram & program)
{
	setScale(.25f);
	return loadFromFile("models/Tomato.obj", program);
}

void Tomato::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/TomatoCutted.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Tomato::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Tomato::isCut()
{
	return cutBool;
}

string Tomato::whatAmI()
{
	return "Tomato";
}

