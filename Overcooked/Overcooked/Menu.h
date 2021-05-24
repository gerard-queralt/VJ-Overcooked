#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Sprite.h"

class Menu
{
public:

	enum Type{MAIN, LEVEL, PAUSE};
	void init(ShaderProgram &shaderProgram);
	void render();

	void setPosition(const glm::vec2 &pos);

	void setType(Menu::Type type);

	void goUp();

	void goDown();

	int getPosition();
	Type getType();

private:
	glm::vec2 position;
	Texture spritesheet;
	Sprite *sprite;

	int posInicialX, posInicialY;

	Type type;
	int currentPosition;

	void changePosition();
};

#endif // _MENU_INCLUDE

