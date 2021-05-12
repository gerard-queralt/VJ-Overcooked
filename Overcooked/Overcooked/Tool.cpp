#include "Tool.h"

#define COOKING_TIME 1000
#define BURN_TIME COOKING_TIME + 500

void Tool::cookFood(int deltaTime)
{
	cookingTime += deltaTime;
	if (COOKING_TIME <= cookingTime && cookingTime < BURN_TIME)
		cookedFood = true;
	else if (BURN_TIME <= cookingTime)
		burnedFood = true;
}

bool Tool::isFood()
{
	return false;
}
