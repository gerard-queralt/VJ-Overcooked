#include "Plate.h"
#include "Level.h"

#include "Beef.h"
#include "Burger.h"

bool Plate::init(ShaderProgram & program)
{
	setScale(0.5f);
	this->program = program;
	return loadFromFile("models/EmptyPlate.obj", program);
}

void Plate::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (onionSoup || mushroomSoup)
		mushroomSoup = onionSoup = !loadFromFile("models/SoupBowl.obj", program);
	if (tomatoSoup)
		tomatoSoup = !loadFromFile("models/TomatoSoupBowl.obj", program);
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
		else if (food->whatAmI() == "TomatoSoup") {
			tomatoSoup = true;
			this->food = food;
			return true;
		}
		else if (food->whatAmI() == "MushroomSoup") {
			mushroomSoup = true;
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
	return assembleRecipe(food);
}

bool Plate::hasFood()
{
	return food != NULL;
}

Food * Plate::getFood()
{
	return food;
}

void Plate::empty()
{
	food = NULL;
}

string Plate::whatAmI()
{
	return "Plate";
}

bool Plate::assembleRecipe(Food* addedFood)
{
	if (partOfBurgerRecipe(food) && partOfBurgerRecipe(addedFood)) {
		//hauriem de destruir el mejar
		food->setScale(0.f);
		food->setPosition(glm::vec3(100.f, 0.f, 100.f));
		addedFood->setScale(0.f);
		addedFood->setPosition(glm::vec3(100.f, 0.f, 100.f));
		Burger* burger = new Burger();
		burger->init(program);
		burger->addIngredient(food);
		burger->addIngredient(addedFood);
		food = burger;
		food->setPosition(glm::vec3(position.x, position.y + model->getHeight() * scale, position.z));
		food->setPlayer(player);
		level->addItem(food);
	}
	else if (food->whatAmI() == "Burger" && partOfBurgerRecipe(addedFood)) {
		if (((Burger*)food)->addIngredient(addedFood)) {
			addedFood->setScale(0.f);
			addedFood->setPosition(glm::vec3(100.f, 0.f, 100.f));
		}
	}
	return false;
}

bool Plate::partOfBurgerRecipe(Food * food)
{
	return food->whatAmI() == "Bread" 
		|| (food->whatAmI() == "Beef" && ((Beef*) food)->isCooked()) 
		|| (food->whatAmI() == "Tomato" && food->isCut())
		|| (food->whatAmI() == "Cheese" && food->isCut());
}
