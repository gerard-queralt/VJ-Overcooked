#ifndef _STOVE_INCLUDE
#define _STOVE_INCLUDE

#include "Table.h"
#include "ParticleSystem.h"

class Stove :
	public Table
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

	bool setItem(Item* item);

private:
	bool playerInExtinguisherDistance();
private:
	Billboard* fireHazard;
	int fireHazardFlashTime;
	ParticleSystem *particles;

	bool burning;
	bool putOut;

	bool facingUpdated = false;
	bool notFacingUpdated = false;

	bool playingFireSound = false;
	bool playingAlarmSound = false;
	bool playingBuringSound = false;
};

#endif //_STOVE_INCLUDE