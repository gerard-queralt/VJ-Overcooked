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
	//Billboard* working;
	Billboard* fireHazard;
	int fireHazardFlashTime;
	ParticleSystem *particles;

	bool burning;
	bool putOut;
};

#endif //_STOVE_INCLUDE