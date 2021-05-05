#include "Player.h"

#define PLAYER_SPEED 0.2

Player::Player()
{
	holding = NULL;
}

void Player::movePlayer(int dir)
{
	switch (dir) {
	case FRONT:
		position.z += PLAYER_SPEED;
		if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z + PLAYER_SPEED));
		break;
	case BACK:
		position.z -= PLAYER_SPEED;
		if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z - PLAYER_SPEED));
		break;
	case LEFT:
		position.x += PLAYER_SPEED;
		if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x + PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		break;
	case RIGHT:
		position.x -= PLAYER_SPEED;
		if (holding != NULL) holding->setPosition(glm::vec3(holding->getPosition().x - PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		break;
	}
}

void Player::hold(Item * item)
{
	if(holding == NULL)
		holding = item;
}

void Player::dropHolding()
{
	holding = NULL;
}
