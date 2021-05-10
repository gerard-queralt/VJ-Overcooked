#include "Player.h"
#include "Game.h"

#define PI 3.14159f

#define PLAYER_SPEED 0.2f
#define ACTION_INTERVAL 300
#define ROTATION_STEP 5.f

bool Player::init(ShaderProgram & program)
{
	setScale(2.f);
	return loadFromFile("models/chr_swordless.obj", program);
}

void Player::update(int deltaTime)
{
	holdDropCD -= deltaTime;
	startStopCutting -= deltaTime;

	if (!cutting) {
		if (Game::instance().getKey('w'))
			movePlayer(FRONT);
		if (Game::instance().getKey('s'))
			movePlayer(BACK);
		if (Game::instance().getKey('a'))
			movePlayer(LEFT);
		if (Game::instance().getKey('d'))
			movePlayer(RIGHT);
	}

	if (holding != NULL && Game::instance().getKey(' '))
		dropHolding();

	//std::vector<glm::vec3> bbox = getBoundingBox();
	//std::vector<glm::vec3> front = getFrontBBox();
}

std::vector<glm::vec3> Player::getFrontBBox()
{
	std::vector<glm::vec3> modelBbox = model->getBoundingBox();
	std::vector<glm::vec3> bbox;
	bbox.resize(2);
	bbox[0] = glm::vec3(modelBbox[0].x, 0.f, modelBbox[1].z);
	bbox[1] = glm::vec3(modelBbox[1].x, 0.f, modelBbox[1].z + 0.1f);

	//l'escalem
	bbox[0] *= scale; // model->getHeight();
	bbox[1] *= scale; // model->getHeight();

	//la rotem
	bbox[0].x = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
	bbox[0].z = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
	bbox[1].x = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
	bbox[1].z = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);

	//la desplacem a la posicio de l'entitat
	bbox[0] += position;
	bbox[1] += position;

	return bbox;
}

void Player::movePlayer(int dir)
{
	float rotation = getRotation();
	switch (dir) {
	case FRONT:
		position.z += PLAYER_SPEED;
		if(level->playerCollision(this))
			position.z -= PLAYER_SPEED;
		else {
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z + PLAYER_SPEED));
		}
		if (rotation != 0) {
			if (rotation <= 180)
				setRotation(rotation - ROTATION_STEP);
			else
				setRotation(rotation + ROTATION_STEP);
		}
		break;
	case BACK:
		position.z -= PLAYER_SPEED;
		if (level->playerCollision(this))
			position.z += PLAYER_SPEED;
		else {
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x, holding->getPosition().y, holding->getPosition().z - PLAYER_SPEED));
		}
		if (rotation != 180) {
			if (rotation < 180)
				setRotation(rotation + ROTATION_STEP);
			else
				setRotation(rotation - ROTATION_STEP);
		}
		break;
	case LEFT:
		position.x += PLAYER_SPEED;
		if (level->playerCollision(this))
			position.x -= PLAYER_SPEED;
		else {
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x + PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		}
		if (rotation != 90) {
			if (rotation < 90 || rotation > 270)
				setRotation(rotation + ROTATION_STEP);
			else
				setRotation(rotation - ROTATION_STEP);
		}
		break;
	case RIGHT:
		position.x -= PLAYER_SPEED;
		if (level->playerCollision(this))
			position.x += PLAYER_SPEED;
		else {
			if (holding != NULL)
				holding->setPosition(glm::vec3(holding->getPosition().x - PLAYER_SPEED, holding->getPosition().y, holding->getPosition().z));
		}
		if (rotation != 270) {
			if (rotation < 90 || rotation > 270)
				setRotation(rotation - ROTATION_STEP);
			else
				setRotation(rotation + ROTATION_STEP);
		}
		break;
	}
	if (holding != NULL)
		holding->setRotation(getRotation());
}

bool Player::hold(Item * item)
{
	if (holdDropCD <= 0 && holding == NULL && Game::instance().getKey(' ')) {
		holding = item;
		holdDropCD = ACTION_INTERVAL;
		return true;
	}
	return false;
}

void Player::dropHolding()
{
	if (holdDropCD <= 0) {
		if (level->putItemOnTable(holding) != Level::FULL) {
			holding = NULL;
			holdDropCD = ACTION_INTERVAL;
		}
	}
}

void Player::checkStartStopCutting()
{
	if (startStopCutting <= 0 && Game::instance().getKey('c') /*hauria de ser CTRL pero en GLUT no se pot*/) {
		cutting = !cutting;
		startStopCutting = ACTION_INTERVAL;
	}
}

bool Player::isCutting()
{
	return cutting;
}

void Player::stopCutting()
{
	cutting = false;
	startStopCutting = ACTION_INTERVAL;
}
