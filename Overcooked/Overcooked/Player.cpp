#include "Player.h"
#include "Game.h"

#define PLAYER_SPEED 0.2
#define HOLD_DROP_INTERVAL 300

bool Player::init(ShaderProgram & program)
{
	return loadFromFile("models/chr_swordless.obj", program);
}

void Player::update(int deltaTime)
{
	holdDropCD -= deltaTime;

	if (Game::instance().getKey('w'))
		movePlayer(FRONT);
	if (Game::instance().getKey('s'))
		movePlayer(BACK);
	if (Game::instance().getKey('a'))
		movePlayer(LEFT);
	if (Game::instance().getKey('d'))
		movePlayer(RIGHT);

	if (holding != NULL && Game::instance().getKey(' '))
		dropHolding();
}

void Player::movePlayer(int dir)
{
	switch (dir) {
	case FRONT:
		position.z += PLAYER_SPEED;
		if(position.z >= level->getSize().z/2)
			position.z -= PLAYER_SPEED;
		else if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z + PLAYER_SPEED));
		break;
	case BACK:
		position.z -= PLAYER_SPEED;
		if (position.z <= - level->getSize().z / 2)
			position.z += PLAYER_SPEED;
		else if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z - PLAYER_SPEED));
		break;
	case LEFT:
		position.x += PLAYER_SPEED;
		if (position.x >= level->getSize().x / 2)
			position.x -= PLAYER_SPEED;
		else if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x + PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		break;
	case RIGHT:
		position.x -= PLAYER_SPEED;
		if (position.x <= - level->getSize().x / 2)
			position.x += PLAYER_SPEED;
		else if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x - PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		break;
	}
}

void Player::hold(Item * item)
{
	if (holdDropCD <= 0 && holding == NULL && Game::instance().getKey(' ')) {
		holding = item;
		holdDropCD = HOLD_DROP_INTERVAL;
	}
}

void Player::dropHolding()
{
	if (holdDropCD <= 0) {
		holding = NULL;
		holdDropCD = HOLD_DROP_INTERVAL;
	}
}
