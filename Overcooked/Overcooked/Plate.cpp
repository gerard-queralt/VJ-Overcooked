#include "Plate.h"

bool Plate::init(ShaderProgram & program)
{
	setScale(0.5f);
	return loadFromFile("models/EmptyPlate.obj", program);
}

void Plate::setPosition(const glm::vec3 pos)
{
	this->position = pos;
	if (this->food != NULL) {
		this->food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
	}
}

bool Plate::addFood(Food * food)
{
	if (this->food == NULL) {
		this->food = food;
		this->food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		return true;
	}
	return false;
}

bool Plate::hasFood()
{
	return food != NULL;
}
