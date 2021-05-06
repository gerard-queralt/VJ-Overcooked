#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"
#include "Item.h"

class Entity;

class Player :
	public Entity
{
public:
	void update(int deltaTime);

	enum PlayerDirections {
		FRONT = 0, BACK, LEFT, RIGHT
	};

	void movePlayer(int dir);

	void hold(Item* item);
	void dropHolding();

private:
	Item *holding;
	int holdDropCD = 0;
};

#endif // _PLAYER_INCLUDE