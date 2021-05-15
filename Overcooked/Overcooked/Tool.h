#ifndef _TOOL_INCLUDE
#define _TOOL_INCLUDE

#include "Item.h"
#include "Food.h"

class Tool :
	public Item
{
public:
	virtual bool addFood(Food* food) = 0;

	virtual bool hasFood() = 0;

	void cookFood(int deltaTime);

	bool isFood();

	#define COOKING_TIME 3000
	#define BURN_TIME COOKING_TIME + 3000

protected:
	bool addedFood = false;
	bool cookedFood = false;
	bool burnedFood = false;

	int cookingTime = 0;

private:
	bool cookedUpdated = false;
	bool burnedUpdated = false;
};

#endif // _TOOL_INCLUDE