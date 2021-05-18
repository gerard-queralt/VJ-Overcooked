#include "Pot.h"
#include "OnionSoup.h"
#include "Trash.h"
#include "Level.h"

#define TIME_SETBACK 1000

bool Pot::init(ShaderProgram & program)
{
	setScale(.5f);
	return loadFromFile("models/EmptyCookingPot.obj", program);
}

void Pot::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (emptied) {
		emptied = !loadFromFile("models/EmptyCookingPot.obj", program);
	}
	if (addedFood) {
		addedFood = !loadFromFile("models/SoupCookingPotMiddleCooked.obj", program);
	}
	if (cookedFood) {
		cookedFood = !loadFromFile("models/SoupCookingPot.obj", program);
		checkRecipe();
	}
	if (burnedFood) {
		burnedFood = !loadFromFile("models/BurnedSoupCookingPot.obj", program);
		this->recipe = new Trash();
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
	if (foods.size() < 4 && foodIsValid(food) && cookingTime < COOKING_TIME) {
		if (foods.empty())
			addedFood = true;
		//food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		food->setScale(0.f);
		foods.push_back(food);
		cookingTime -= TIME_SETBACK;
		return true;
	}
	return false;
}

bool Pot::hasFood()
{
	return !foods.empty();
}

bool Pot::finished()
{
	return recipe != NULL;
}

Food * Pot::getFinishedRecipe()
{
	return recipe;
}

void Pot::empty()
{
	recipe = NULL;
	emptied = true;
}

string Pot::whatAmI()
{
	return "Pot";
}

bool Pot::foodIsValid(Food * food)
{
	return food->whatAmI() == "Onion" && food->isCut();
}

void Pot::checkRecipe()
{
	if (foods.size() == 3) {
		if (foods[0]->whatAmI() == "Onion" && foods[1]->whatAmI() == "Onion" && foods[2]->whatAmI() == "Onion") {
			recipe = new OnionSoup();
		}
		else {
			this->recipe = new Trash();
		}
	}
	else {
		this->recipe = new Trash();
	}
	//no funciona
	//for (Food* f : foods) {
		//level->removeItem(f);
	//}
	foods.clear();
}
