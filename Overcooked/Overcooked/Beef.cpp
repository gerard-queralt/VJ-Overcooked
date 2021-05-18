#include "Beef.h"

bool Beef::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/Beef.obj", program);
}

void Beef::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!cutUpdated) {
		cutUpdated = loadFromFile("models/RawBurger.obj", program);
	}
	if (!cookedUpdated) {
		cookedUpdated = loadFromFile("models/chr_swordless.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Beef::cut()
{
	if (!cutBool) {
		cutBool = true;
		cutUpdated = false;
	}
}

bool Beef::isCut()
{
	return cutBool;
}

void Beef::cook()
{
	if (!cookedBool) {
		cookedBool = true;
		cookedUpdated = false;
	}
}

bool Beef::isCooked()
{
	return cookedBool;
}

string Beef::whatAmI()
{
	return "Beef";
}
