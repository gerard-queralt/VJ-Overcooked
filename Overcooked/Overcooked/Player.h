#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Item.h"
#include "ParticleSystem.h"

class Entity;

class Player :
	public Entity
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

	std::vector<glm::vec3> getFrontBBox();
	std::vector<glm::vec3> getExtinguisherBBox();

	enum PlayerDirections {
		FRONT = 0, BACK, LEFT, RIGHT
	};

	void movePlayer(int dir);

	bool hold(Item* item);
	void dropHolding();

	void checkStartStopCutting();
	bool isCutting();
	void stopCutting();

	bool holdingPlate();
	bool usingExtinguisher();

	bool godModeOn();
	bool checkFinishCooking();
	bool fireproofOn();
	bool timeFrozen();

private:
	void adjustItemPosition();

private:
	ParticleSystem *particles;
	bool walking = false;

	bool cutting = false;

	Item *holding;
	int holdDropCD = 0;
	int startStopCutting = 0;
	int startStopExtinguisher = 0;
	int godModeInputsCD = 0;

	bool godMode = false;
	bool finishCooking = false;
	bool fireproof = false;
	bool theWorld = false;

	bool playingSound;
};

#endif // _PLAYER_INCLUDE