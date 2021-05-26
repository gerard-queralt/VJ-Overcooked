#include "Tool.h"
#include "Player.h"

void Tool::cookFood(int deltaTime)
{
	cookingTime += deltaTime;
	
	if (player->checkFinishCooking() || (player->fireproofOn() && cookingTime > COOKING_TIME)) {
		cookingTime = COOKING_TIME;
	}

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

bool Tool::finished()
{
	return false;
}

Food * Tool::getFood()
{
	return NULL;
}
