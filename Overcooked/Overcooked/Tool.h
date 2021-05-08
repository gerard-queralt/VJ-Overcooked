#ifndef _TOOL_INCLUDE
#define _TOOL_INCLUDE

#include "Item.h"
#include "Food.h"

class Tool :
	public Item
{
public:
	virtual bool addFood(Food* food) = 0;

	bool isFood();
};

#endif // _TOOL_INCLUDE