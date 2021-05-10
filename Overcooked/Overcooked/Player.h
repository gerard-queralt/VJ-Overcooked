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

	std::vector<glm::vec3> getFrontBBox();

	enum PlayerDirections {
		FRONT = 0, BACK, LEFT, RIGHT
	};

	void movePlayer(int dir);

	bool hold(Item* item);
	void dropHolding();

	void checkStartStopCutting();
	bool isCutting();
	void stopCutting();

private:
	bool cutting = false;

	Item *holding;
	int holdDropCD = 0;
	int startStopCutting = 0;
};

#endif // _PLAYER_INCLUDE