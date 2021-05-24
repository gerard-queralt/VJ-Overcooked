#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Sprite.h"

class Menu
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

	int posInicialX, posInicialY;
};

#endif // _MENU_INCLUDE

