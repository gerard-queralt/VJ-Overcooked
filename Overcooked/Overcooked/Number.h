#ifndef _NUMBER_INCLUDE
#define _NUMBER_INCLUDE

#include "Sprite.h"

class Number
{
public:
	void init(const glm::vec2 &pos, ShaderProgram &shaderProgram);
	virtual void render();
	void changeNumber(int n);

private:
	glm::vec2 position;
	Texture spritesheet;
	Sprite *sprite;
};

#endif // _NUMBER_INCLUDE