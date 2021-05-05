#include "Player.h"
#include "Game.h"

#define PLAYER_SPEED 0.2

void Player::update(int deltaTime)
{
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
	if(holding == NULL && Game::instance().getKey(' '))
		holding = item;
}

void Player::dropHolding()
{
	holding = NULL;
}
