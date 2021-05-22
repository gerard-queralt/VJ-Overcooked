#include "DeliveryConveyor.h"
#include "Level.h"
#include "Plate.h"

bool DeliveryConveyor::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/DeliveryConveyor.obj", program);
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
