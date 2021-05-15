#include "Plate.h"

bool Plate::init(ShaderProgram & program)
{
	setScale(0.5f);
	return loadFromFile("models/EmptyPlate.obj", program);
}

void Plate::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (onionSoup)
		onionSoup = !loadFromFile("models/SoupBowl.obj", program);
	if(trash)
		trash = !loadFromFile("models/BurnedSoupBowl.obj", program);
	Entity::render(program, viewMatrix);
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
		if (food->whatAmI() == "OnionSoup") {
			onionSoup = true;
			this->food = food;
			return true;
		}
		else if (food->whatAmI() == "Trash") {
			trash = true;
			this->food = food;
			return true;
		}
		else {
			this->food = food;
			this->food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
			return true;
		}
	}
	return false;
}

bool Plate::hasFood()
{
	return food != NULL;
}

string Plate::whatAmI()
{
	return "Plate";
}
