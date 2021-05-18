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
	if (this->item != NULL && !item->isFood()) {
		if (0 < ((Tool*) item)->getCookingTime() && ((Tool*)item)->getCookingTime() < COOKING_TIME) {
			glm::mat4 modelMatrix;
			glm::mat3 normalMatrix;
			glm::vec3 obs = glm::vec3(0.f, 24.f, -30.f);

			program.setUniform1b("bLighting", false);
			modelMatrix = glm::mat4(1.0f);
			program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
			normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
			program.setUniformMatrix3f("normalmatrix", normalMatrix);
			working->render(glm::vec3(position.x, 1.f, position.z), obs);
			program.setUniform1b("bLighting", true);
		}
	}
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
