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
		if (hasTomato || hasCheese || hasLettuce)
			return false;
		hasTomato = true;
	}
	else if (food->whatAmI() == "Cheese") {
		if (hasTomato || hasCheese || hasLettuce)
			return false;
		hasCheese = true;
	}
	else if (food->whatAmI() == "Lettuce") {
		if (hasTomato || hasCheese || hasLettuce)
			return false;
		hasLettuce = true;
	}
	if (hasBeef) {
		if (hasBread) {
			if (hasTomato) {
				return loadFromFile("models/BurgerBreadTomato.obj", program);
			}
			if (hasCheese) {
				return loadFromFile("models/BurgerBreadCheese.obj", program);
			}
			if (hasLettuce) {
				return loadFromFile("models/BurgerBreadLettuce.obj", program);
			}
			return loadFromFile("models/BurgerBread.obj", program);
		}
		if (hasTomato) {
			return loadFromFile("models/BurgerTomato.obj", program);
		}
		if (hasCheese) {
			return loadFromFile("models/BurgerCheese.obj", program);
		}
		if (hasLettuce) {
			return loadFromFile("models/BurgerLettuce.obj", program);
		}
	}
	if (hasBread) {
		if (hasTomato) {
			return loadFromFile("models/BreadTomato.obj", program);
		}
		if (hasCheese) {
			return loadFromFile("models/BreadCheese.obj", program);
		}
		if (hasLettuce) {
			return loadFromFile("models/BreadLettuce.obj", program);
		}
	}
}

string Burger::whatAmI()
{
	return "Burger";
}
