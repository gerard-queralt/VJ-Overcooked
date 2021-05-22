#include "Number.h"

void Number::init(const glm::vec2 & pos, ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/numbersSprites.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(26, 26), glm::vec2(0.1f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.1f, 0.f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.2f, 0.f));

	sprite->setAnimationSpeed(3, 8);
	sprite->addKeyframe(3, glm::vec2(0.3f, 0.f));

	sprite->setAnimationSpeed(4, 8);
	sprite->addKeyframe(4, glm::vec2(0.4f, 0.f));

	sprite->setAnimationSpeed(5, 8);
	sprite->addKeyframe(5, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(6, 8);
	sprite->addKeyframe(6, glm::vec2(0.6f, 0.f));

	sprite->setAnimationSpeed(7, 8);
	sprite->addKeyframe(7, glm::vec2(0.7f, 0.f));

	sprite->setAnimationSpeed(8, 8);
	sprite->addKeyframe(8, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(9, 8);
	sprite->addKeyframe(9, glm::vec2(0.9f, 0.f));

	position = pos;
	sprite->setPosition(position);
}

void Number::render()
{
	sprite->render();
}

void Number::setPosition(const glm::vec2 & pos)
{
	position = pos;
	sprite->setPosition(position);
}

void Number::changeNumber(int n)
{
	sprite->changeAnimation(n);
}
