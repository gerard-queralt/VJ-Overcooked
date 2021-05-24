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

	int getCookingTime();

	virtual bool finished();
	virtual Food* getFood();
	virtual void empty() = 0;

	#define COOKING_TIME 5000
	#define BURN_TIME COOKING_TIME + 10000

protected:
	bool cookedFood = false;
	bool burnedFood = false;
	bool cookedUpdated = false;
	bool burnedUpdated = false;

	int cookingTime = 0;	
};

#endif // _TOOL_INCLUDE