#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Sprite.h"

class Menu
{
public:

	enum Type{MAIN, LEVEL, PAUSE, HOW};
	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);

	void setType(Menu::Type type);

	void goUp();

	void goDown();

	int getPosition();
	Type getType();

private:
	void changePosition();

private:
	glm::vec2 position;
	Texture spritesheet;
	Sprite *sprite;

	int posInicialX, posInicialY;

	Type type;
	int currentPosition;
	int currentTime;
};

#endif // _MENU_INCLUDE

