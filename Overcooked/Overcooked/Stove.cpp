#include "Stove.h"
#include "Tool.h"

bool Stove::init(ShaderProgram & program)
{
	setScale(1.f);
	working = Billboard::createBillboard(glm::vec2(1.f, 1.f), program, "images/tmpHourglass.png");
	working->setType(BILLBOARD_Y_AXIS);
	return loadFromFile("models/Stove.obj", program);
}

void Stove::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	Entity::render(program, viewMatrix);
}

void Stove::update(int deltaTime)
{
	Table::update(deltaTime);
	if (item != NULL && ((Tool*)item)->hasFood()) {
		((Tool*)item)->cookFood(deltaTime);
	}
}

bool Stove::setItem(Item * item)
{
	if (this->item == NULL && !item->isFood()) {
		item->setPosition(glm::vec3(position.x, 1.2f, position.z));
		this->item = item;
		return true;
	}
	else if (this->item != NULL && !this->item->isFood() && item->isFood()) {
		return ((Tool*) this->item)->addFood((Food*)item);
	}
	return false;
}
