#include "TrashCan.h"
#include "Tool.h"

bool TrashCan::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/TrashCan.obj", program);
}

bool TrashCan::setItem(Item * item)
{
	if (item->isFood()) {
		item->setPosition(position);
		item->setScale(0.f);
		return true;
	}
	else if(((Tool*) item)->hasFood()){
		if ((item)->whatAmI() != "Pot") {
			((Tool*)item)->getFood()->setPosition(position);
			((Tool*)item)->getFood()->setScale(0.f);
		}
		((Tool*)item)->empty();
	}
	return false;
}
