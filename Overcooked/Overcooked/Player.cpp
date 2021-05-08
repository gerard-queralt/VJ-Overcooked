#include "Player.h"
#include "Game.h"

#define PLAYER_SPEED 0.2
#define HOLD_DROP_INTERVAL 300
#define ROTATION_STEP 5.f

bool Player::init(ShaderProgram & program)
{
	setScale(2.f);
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
		if(level->playerCollision(this))
			position.z -= PLAYER_SPEED;
		else {
			float rotation = getRotation();
			if (rotation != 0) {
				if (rotation <= 180)
					setRotation(rotation - ROTATION_STEP);
				else
					setRotation(rotation + ROTATION_STEP);
			}
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z + PLAYER_SPEED));
		}
		break;
	case BACK:
		position.z -= PLAYER_SPEED;
		if (level->playerCollision(this))
			position.z += PLAYER_SPEED;
		else {
			float rotation = getRotation();
			if (rotation != 180) {
				if (rotation < 180)
					setRotation(rotation + ROTATION_STEP);
				else
					setRotation(rotation - ROTATION_STEP);
			}
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z - PLAYER_SPEED));
		}
		break;
	case LEFT:
		position.x += PLAYER_SPEED;
		if (level->playerCollision(this))
			position.x -= PLAYER_SPEED;
		else {
			float rotation = getRotation();
			if (rotation != 90) {
				if (rotation < 90 || rotation > 270)
					setRotation(rotation + ROTATION_STEP);
				else
					setRotation(rotation - ROTATION_STEP);
			}
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x + PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		}
		break;
	case RIGHT:
		position.x -= PLAYER_SPEED;
		if (level->playerCollision(this))
			position.x += PLAYER_SPEED;
		else {
			float rotation = getRotation();
			if (rotation != 270) {
				if (rotation < 90 || rotation > 270)
					setRotation(rotation - ROTATION_STEP);
				else
					setRotation(rotation + ROTATION_STEP);
			}
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x - PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		}
		break;
	}
	if (holding != NULL)
		holding->setRotation(getRotation());
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
		if (level->putItemOnTable(holding) != Level::FULL) {
			holding = NULL;
			holdDropCD = HOLD_DROP_INTERVAL;
		}
	}
}
