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

protected:
	bool addedFood = false;
	bool cookedFood = false;
	bool burnedFood = false;

private:
	int cookingTime = 0;
};

#endif // _TOOL_INCLUDE