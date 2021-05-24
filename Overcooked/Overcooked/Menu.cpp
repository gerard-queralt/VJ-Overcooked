#include "Menu.h"

void Menu::init(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/fletxaSeleccio.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);

}

void Menu::render()
{
	sprite->render();
}

void Menu::setPosition(const glm::vec2 & pos)
{
	position = pos;
	sprite->setPosition(position);
}

void Menu::setType(Menu::Type type) {
	this->type = type;
	currentPosition = 0;
	changePosition();
}

void Menu::goUp()
{
	--currentPosition;
	if (currentPosition == -1) {
		if (type == MAIN)
			currentPosition = 2;
		if (type == LEVEL)
			currentPosition = 4;
	}
	changePosition();
}

void Menu::goDown()
{
	++currentPosition;
	if (type == MAIN && currentPosition > 2)
		currentPosition = 0;
	if (type == LEVEL && currentPosition > 4)
		currentPosition = 0;
	changePosition();
}

int Menu::getPosition()
{
	return currentPosition;
}

Menu::Type Menu::getType()
{
	return type;
}

void Menu::changePosition()
{
	switch (type)
	{
	case Menu::MAIN:
		switch (currentPosition)
		{
		case 0: setPosition(glm::vec2(11.5f * 32.f, 6.45f * 32.f));
			break;
		case 1: setPosition(glm::vec2(13.5f * 32.f, 7.60f * 32.f));
			break;
		case 2: setPosition(glm::vec2(10.5f * 32.f, 8.9f * 32.f));
			break;
		default:
			break;
		}
		break;
	case Menu::LEVEL:
		switch (currentPosition)
		{
		case 0: setPosition(glm::vec2(12.25f * 32.f, 5.25f * 32.f));
			break;
		case 1: setPosition(glm::vec2(12.25f * 32.f, 6.3f * 32.f));
			break;
		case 2: setPosition(glm::vec2(12.25f * 32.f, 7.35f * 32.f));
			break;
		case 3: setPosition(glm::vec2(12.25f * 32.f, 8.4f * 32.f));
			break;
		case 4: setPosition(glm::vec2(12.25f * 32.f, 9.45f * 32.f));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

