#ifndef _FOOD_INCLUDE
#define _FOOD_INCLUDE

#include "Item.h"

class Food :
	public Item
{
public:
	bool isFood();

	virtual void cut();
	virtual bool isCut();
	virtual bool isCooked();
	virtual bool recipeDone();
};

#endif // _FOOD_INCLUDE