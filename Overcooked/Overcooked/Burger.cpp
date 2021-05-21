#include "Burger.h"

bool Burger::init(ShaderProgram & program)
{
	setScale(.5f);
	this->program = program;
	return true;
}

bool Burger::addIngredient(Food * food)
{
	if (food->whatAmI() == "Beef") {
		if (hasBeef)
			return false;
		hasBeef = true;
	}
	else if (food->whatAmI() == "Bread") {
		if (hasBread)
			return false;
		hasBread = true;
	}
	else if (food->whatAmI() == "Tomato") {
		if (hasTomato || hasCheese)
			return false;
		hasTomato = true;
	}
	else if (food->whatAmI() == "Cheese") {
		if (hasTomato || hasCheese)
			return false;
		hasCheese = true;
	}
	if (hasBeef) {
		if (hasBread) {
			if (hasTomato) {
				return loadFromFile("models/BurgerBreadTomato.obj", program);
			}
			return loadFromFile("models/BurgerBread.obj", program);
		}
		if (hasTomato) {
			return loadFromFile("models/BurgerTomato.obj", program);
		}
	}
	if (hasBread) {
		if (hasTomato) {
			return loadFromFile("models/BreadTomato.obj", program);
		}
	}
}

string Burger::whatAmI()
{
	return "Burger";
}
