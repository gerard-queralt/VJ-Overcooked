#include "Menu.h"

#include "Music.h"

void Menu::init(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/fletxaSeleccio.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);

}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;
	float displacement = sin( ((float) currentTime) / 200.f) * 8.f;
	sprite->setPosition(glm::vec2(position.x + displacement, position.y));
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
			currentPosition = 5;
		if (type == PAUSE)
			currentPosition = 2;
	}

	Music::instance().playSoundEffect(4);

	changePosition();
}

void Menu::goDown()
{
	++currentPosition;
	if (type == MAIN && currentPosition > 2)
		currentPosition = 0;
	if (type == LEVEL && currentPosition > 5)
		currentPosition = 0;
	if(type == PAUSE && currentPosition > 2)
		currentPosition = 0;

	Music::instance().playSoundEffect(4);

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
		case 0: setPosition(glm::vec2(12.75f * 32.f, 5.f * 32.f));
			break;
		case 1: setPosition(glm::vec2(15.75f * 32.f, 7.f * 32.f));
			break;
		case 2: setPosition(glm::vec2(11.75f * 32.f, 9.f * 32.f));
			break;
		default:
			break;
		}
		break;
	case Menu::LEVEL:
		switch (currentPosition)
		{
		case 0: setPosition(glm::vec2(12.5f * 32.f, 5.f * 32.f));
			break;
		case 1: setPosition(glm::vec2(12.5f * 32.f, 6.f * 32.f));
			break;
		case 2: setPosition(glm::vec2(12.5f * 32.f, 7.f * 32.f));
			break;
		case 3: setPosition(glm::vec2(12.5f * 32.f, 8.f * 32.f));
			break;
		case 4: setPosition(glm::vec2(12.5f * 32.f, 9.f * 32.f));
			break;
		case 5: setPosition(glm::vec2(12.5f * 32.f, 10.f * 32.f));
		default:
			break;
		}
		break;
	case Menu::PAUSE:
		switch (currentPosition)
		{
		case 0: setPosition(glm::vec2(12.75f * 32.f, 5.f * 32.f));
			break;
		case 1: setPosition(glm::vec2(15.75f * 32.f, 7.f * 32.f));
			break;
		case 2: setPosition(glm::vec2(11.75f * 32.f, 9.1f * 32.f));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	currentTime = 0;
}

