#include "Tool.h"

#define COOKING_TIME 1000
#define BURN_TIME COOKING_TIME + 300000000000

void Tool::cookFood(int deltaTime)
{
	cookingTime += deltaTime;
	if (COOKING_TIME <= cookingTime && cookingTime < BURN_TIME && !cookedUpdated) {
		cookedFood = true;
		cookedUpdated = true;
	}
	else if (BURN_TIME <= cookingTime && !burnedUpdated) {
		burnedFood = true;
		burnedUpdated = true;
	}
}

bool Tool::isFood()
{
	return false;
}
