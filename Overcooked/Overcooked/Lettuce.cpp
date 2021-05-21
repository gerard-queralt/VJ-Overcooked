#include "Lettuce.h"

bool Lettuce::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/Lettuce.obj", program);
}

void Lettuce::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/CutLettuce.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Lettuce::cut()
{
	if (!cutBool) {
		cutBool = true;
		updated = false;
	}
}

bool Lettuce::isCut()
{
	return cutBool;
}

string Lettuce::whatAmI()
{
	return "Lettuce";
}
