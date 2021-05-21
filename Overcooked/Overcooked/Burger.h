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

private:
	ShaderProgram program;

	bool hasBeef = false;
	bool hasBread = false;
	bool hasTomato = false;
	bool hasCheese = false;
};

#endif //_BURGER_INCLUDE