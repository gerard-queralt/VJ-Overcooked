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
		cookedUpdated = loadFromFile("models/Burger.obj", program);
	}
	if (!burnedUpdated) {
		burnedUpdated = loadFromFile("models/BurnedBurger.obj", program);
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

void Beef::burn()
{
	if (!burnedBool) {
		burnedBool = true;
		burnedUpdated = false;
	}
}

bool Beef::isBurned()
{
	return burnedBool;
}

string Beef::whatAmI()
{
	return "Beef";
}
