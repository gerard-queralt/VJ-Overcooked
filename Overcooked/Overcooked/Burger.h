#ifndef _BURGER_INCLUDE
#define _BURGER_INCLUDE

#include "Food.h"

class Burger :
	public Food
{
public:
	bool init(ShaderProgram &program);

	bool addIngredient(Food* food);

	string whatAmI();

	enum Toppings {
		NOTHING = 0, CHEESE, TOMATO, LETTUCE, UNFINISHED
	};
	Toppings getTopping();

	Item* clone();

private:
	ShaderProgram program;

	bool hasBeef = false;
	bool hasBread = false;
	bool hasTomato = false;
	bool hasCheese = false;
	bool hasLettuce = false;
};

#endif //_BURGER_INCLUDE