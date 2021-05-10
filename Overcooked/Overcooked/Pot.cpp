#include "Pot.h"

bool Pot::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/EmptyCookingPot.obj", program);
}

void Pot::setPosition(const glm::vec3 pos)
{
	this->position = pos;
	for (int f = 0; f < foods.size(); ++f) {
		foods[f]->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
	}
}

bool Pot::addFood(Food * food)
{
	if (foods.size() < 4 && food->whatAmI() == "Onion" && food->isCut()) {
		food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		foods.push_back(food);
		return true;
	}
	return false;
}
