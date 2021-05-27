#include "DeliveryConveyor.h"
#include "Level.h"
#include "Plate.h"

bool DeliveryConveyor::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/DeliveryConveyor.obj", program);
}

void DeliveryConveyor::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	/*if (playerFacingThis() && !facingUpdated) {
	loadFromFile("models/EmptyTableSoft.obj", program);
	facingUpdated = true;
	notFacingUpdated = false;
	}
	else if(!playerFacingThis() && !notFacingUpdated){
	loadFromFile("models/EmptyTable.obj", program);
	notFacingUpdated = true;
	facingUpdated = false;
	}*/
	Entity::render(program, viewMatrix);
}

bool DeliveryConveyor::setItem(Item * item)
{
	if (this->item == NULL && item->whatAmI() == "Plate" && ((Plate*) item)->getFood() != NULL) {
		if (level->deliver(((Plate*)item)->getFood())) {
			((Plate*)item)->empty();
			item->setPosition(glm::vec3(position.x, 1.5f, position.z));
			this->item = item;
			return true;
		 }
	}
	return false;
}
