#include "Pot.h"

bool Pot::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/EmptyCookingPot.obj", program);
}

void Pot::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (!updated) {
		updated = loadFromFile("models/SoupCookingPot.obj", program);
	}
	Entity::render(program, viewMatrix);
}

void Pot::setPosition(const glm::vec3 pos)
{
	this->position = pos;
	//for (int f = 0; f < foods.size(); ++f) {
		//foods[f]->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
	//}
}

bool Pot::addFood(Food * food)
{
	if (foods.size() < 4 && foodIsValid(food) && food->isCut()) {
		if (foods.empty())
			updated = false;
		//food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		food->setScale(0.f);
		foods.push_back(food);
		return true;
	}
	return false;
}

bool Pot::foodIsValid(Food * food)
{
	return food->whatAmI() == "Onion";
}
