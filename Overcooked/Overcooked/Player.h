#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Item.h"

class Entity;

class Player :
	public Entity
{
public:
	bool init(ShaderProgram &program);

	void update(int deltaTime);

	enum PlayerDirections {
		FRONT = 0, BACK, LEFT, RIGHT
	};

	void movePlayer(int dir);

	bool hold(Item* item);
	void dropHolding();

	bool isCutting();

private:
	bool cutting = false;

	Item *holding;
	int holdDropCD = 0;
	int startStopCutting = 0;
};

#endif // _PLAYER_INCLUDE