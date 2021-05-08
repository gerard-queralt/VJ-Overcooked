#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Entity.h"

class Item :
	public Entity
{
public:
	void update(int deltaTime);

	virtual bool isFood() = 0;
};

#endif // _ITEM_INCLUDE