#include "FryingPan.h"

bool FryingPan::init(ShaderProgram & program)
{
	setScale(0.75f);
	return loadFromFile("models/Pan.obj", program);
}

void FryingPan::setPosition(const glm::vec3 pos)
{
	this->position = pos;
	if (this->food != NULL) {
		this->food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
	}
}


bool FryingPan::addFood(Food * food)
{
	if (this->food == NULL) {
		this->food = food;
		this->food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		return true;
	}
	return false;
}

bool FryingPan::hasFood()
{
	return food != NULL;
}

string FryingPan::whatAmI()
{
	return "FryingPan";
}
