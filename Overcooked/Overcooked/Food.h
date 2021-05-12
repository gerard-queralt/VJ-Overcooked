#ifndef _FOOD_INCLUDE
#define _FOOD_INCLUDE

#include "Item.h"

class Food :
	public Item
{
public:
	bool isFood();

	virtual void cut() = 0;
	virtual bool isCut();
	virtual bool isCooked();
	virtual bool recipeDone();

	virtual string whatAmI() = 0;
};

#endif // _FOOD_INCLUDE