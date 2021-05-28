#include "Pot.h"
#include "OnionSoup.h"
#include "TomatoSoup.h"
#include "MushroomSoup.h"
#include "Trash.h"
#include "Level.h"

#include "Music.h"

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
		if (foods.size() > 0 && foods[0]->whatAmI() == "Tomato")
			tomatoSoup = true;
		if (tomatoSoup) {
			addedFood = !loadFromFile("models/TomatoSoupCookingPotMiddleCooked.obj", program);
		}
		else {
			addedFood = !loadFromFile("models/SoupCookingPotMiddleCooked.obj", program);
		}
	}
	if (cookedFood) {
		if (foods.size() > 0 && foods[0]->whatAmI() == "Tomato")
			tomatoSoup = true;
		if (tomatoSoup) {
			cookedFood = !loadFromFile("models/TomatoSoupCookingPot.obj", program);
		}
		else {
			cookedFood = !loadFromFile("models/SoupCookingPot.obj", program);
		}
		checkRecipe();

		Music::instance().playSoundEffect(5);
	}
	if (burnedFood) {
		burnedFood = !loadFromFile("models/BurnedSoupCookingPot.obj", program);
		this->recipe = new Trash();
	}
	Tool::render(program, viewMatrix);
}

void Pot::setPosition(const glm::vec3 pos)
{
	this->position = pos;
}

bool Pot::addFood(Food * food)
{
	if (foods.size() < 3 && foodIsValid(food) && cookingTime < COOKING_TIME) {
		if (foods.empty())
			addedFood = true;
		else {
			cookingTime -= TIME_SETBACK;
			if (cookingTime < 0)
				cookingTime = 0;
		}
		food->setPosition(glm::vec3(100.f, 0.f, 100.f));
		food->setScale(0.f);
		foods.push_back(food);
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

Food * Pot::getFood()
{
	return recipe;
}

void Pot::empty()
{
	recipe = NULL;
	emptied = true;
	cookedFood = false;
	cookedUpdated = false;
	burnedFood = false;
	burnedUpdated = false;
	tomatoSoup = false;
	//no funciona
	//for (Food* f : foods) {
	//level->removeItem(f);
	//}
	foods.clear();
	cookingTime = 0;
}

string Pot::whatAmI()
{
	return "Pot";
}

bool Pot::foodIsValid(Food * food)
{
	return (food->whatAmI() == "Onion" && food->isCut()) || (food->whatAmI() == "Tomato" && food->isCut()) || (food->whatAmI() == "Mushroom" && food->isCut());
}

void Pot::checkRecipe()
{
	if (foods.size() == 3) {
		if (foods[0]->whatAmI() == "Onion" && foods[1]->whatAmI() == "Onion" && foods[2]->whatAmI() == "Onion") {
			recipe = new OnionSoup();
		}
		else if (foods[0]->whatAmI() == "Tomato" && foods[1]->whatAmI() == "Tomato" && foods[2]->whatAmI() == "Tomato") {
			recipe = new TomatoSoup();
		}
		else if (foods[0]->whatAmI() == "Mushroom" && foods[1]->whatAmI() == "Mushroom" && foods[2]->whatAmI() == "Mushroom") {
			recipe = new MushroomSoup();
		}
		else {
			this->recipe = new Trash();
		}
	}
	else {
		this->recipe = new Trash();
	}
	tomatoSoup = false;
	//foods.clear();
}
