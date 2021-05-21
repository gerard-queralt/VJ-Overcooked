#include "FryingPan.h"
#include "Beef.h"

bool FryingPan::init(ShaderProgram & program)
{
	setScale(0.75f);
	return loadFromFile("models/Pan.obj", program);
}

void FryingPan::update(int deltaTime)
{
	if (cookedFood) {
		((Beef*)food)->cook();
		cookedFood = false;
	}
	if (burnedFood) {
		((Beef*)food)->burn();
		burnedFood = false;
	}
	Item::update(deltaTime);
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
	if (this->food == NULL && foodIsValid(food)) {
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

bool FryingPan::finished()
{
	if (food != NULL) {
		return ((Beef*)food)->isCooked();
	}
	return false;
}

Food * FryingPan::getFood()
{
	return food;
}

void FryingPan::empty()
{
	food = NULL;
	cookingTime = 0;
}

string FryingPan::whatAmI()
{
	return "FryingPan";
}

bool FryingPan::foodIsValid(Food * food)
{
	return food->whatAmI()=="Beef" && food->isCut() && !((Beef*) food)->isCooked();
}
