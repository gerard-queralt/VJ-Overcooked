#ifndef _NUMBER_INCLUDE
#define _NUMBER_INCLUDE

#include "Sprite.h"

class Number
{
public:
	void init(const glm::vec2 &pos, ShaderProgram &shaderProgram);
	void render();

	void setPosition(const glm::vec2 &pos);

	void changeNumber(int n);

private:
	glm::vec2 position;
	Texture spritesheet;
	Sprite *sprite;
};

#endif // _NUMBER_INCLUDE