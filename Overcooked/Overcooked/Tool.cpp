#include "Tool.h"

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

int Tool::getCookingTime()
{
	return cookingTime;
}
