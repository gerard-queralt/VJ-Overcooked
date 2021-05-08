#ifndef _TABLE_INCLUDE
#define _TABLE_INCLUDE

#include "Entity.h"
#include "Item.h"

class Table :
	public Entity
{
public:
	virtual bool init(ShaderProgram &program);

	void setItem(Item* item);

	bool collisionWithPlayer();

protected:
	Item* item = NULL;
};

#endif //_TABLE_INCLUDE