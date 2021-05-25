#ifndef _EXTINGUISHER_INCLUDE
#define _EXTINGUISHER_INCLUDE

#include "Item.h"
#include "ParticleSystem.h"

class Extinguisher :
	public Item
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

	void changeState();
	bool isActive();
	void stop();

	bool isFood();
	string whatAmI();

private:
	ParticleSystem *particles;
	bool inUse;
};

#endif // _EXTINGUISHER_INCLUDE