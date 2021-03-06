#include "Player.h"
#include "Game.h"
#include "Tool.h"
#include "Extinguisher.h"
#include "Plate.h"

#include "Music.h"

#define PI 3.14159f

#define PLAYER_SPEED 0.2f
#define ACTION_INTERVAL 300
#define ROTATION_STEP 5.f

bool Player::init(ShaderProgram & program)
{
	setScale(1.f);

	playingSound = false;

	// Initialize particle system
	ParticleSystem::Particle particle;
	particle.lifetime = 1e10f;
	particles = new ParticleSystem();
	particles->init(glm::vec2(0.5f, 0.5f), program, "images/dust.png", 2.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return loadFromFile("models/Chef.obj", program);
}

void Player::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	Entity::render(program, viewMatrix);

	//render particles
	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;
	glm::vec3 obs = glm::vec3(0.f, 36.f, -24.f);

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	modelMatrix = glm::mat4(1.0f);
	program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
	normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
	program.setUniformMatrix3f("normalmatrix", normalMatrix);
	program.setUniform2f("texCoordDispl", 0.f, 0.f);
	particles->render(obs);

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	program.setUniform1b("bLighting", true);

}

void Player::update(int deltaTime)
{
	holdDropCD -= deltaTime;
	startStopCutting -= deltaTime;
	startStopExtinguisher -= deltaTime;
	godModeInputsCD -= deltaTime;

	bool walkingInupt = false;
	if (!cutting) {
		if (Game::instance().getKey('w') || Game::instance().getKey('W')) {
			movePlayer(FRONT);
			walkingInupt = true;
		}
		if (Game::instance().getKey('s') || Game::instance().getKey('S')) {
			movePlayer(BACK);
			walkingInupt = true;
		}
		if (Game::instance().getKey('a') || Game::instance().getKey('A')) {
			movePlayer(LEFT);
			walkingInupt = true;
		}
		if (Game::instance().getKey('d') || Game::instance().getKey('D')) {
			movePlayer(RIGHT);
			walkingInupt = true;
		}
	}
	walking = walkingInupt;
	if (walking && !playingSound) {
		Music::instance().playSoundEffect(3);
		playingSound = true;
	}
	else if (!walking && playingSound) {
		Music::instance().stopSoundEffect(3);
		playingSound = false;
	}

	if (holding != NULL && Game::instance().getKey(' '))
		dropHolding();

	if(holding != NULL && holding->whatAmI() == "Extinguisher" && startStopExtinguisher <= 0 && (Game::instance().getKey('c') || Game::instance().getKey('C'))){
		((Extinguisher*)holding)->changeState();
		startStopExtinguisher = ACTION_INTERVAL;
	}

	if (godModeInputsCD <= 0 && (Game::instance().getKey('g') || Game::instance().getKey('G'))) {
		godMode = !godMode;
		godModeInputsCD = ACTION_INTERVAL;
		if (!godMode) {
			fireproof = false;
			theWorld = false;
		}
	}

	if (godModeInputsCD <= 0 && godMode && (Game::instance().getKey('r') || Game::instance().getKey('R') || Game::instance().getKey('1'))) {
		Item* nextRecipe = level->getNextPendingRecipe();
		if (nextRecipe != NULL && holding == NULL) {
			holding = nextRecipe;
			level->addItem(holding);
			holding->setPlayer(this);
			adjustItemPosition();
			if (((Plate*)holding)->getFood()->whatAmI() == "Burger" || ((Plate*)holding)->getFood()->whatAmI() == "Salad") {
				level->addItem(((Plate*)holding)->getFood());
				((Plate*)holding)->getFood()->setPlayer(this);
			}
			holdDropCD = ACTION_INTERVAL;
			godModeInputsCD = ACTION_INTERVAL;
		}
	}

	finishCooking = false;
	if (godModeInputsCD <= 0 && godMode && (Game::instance().getKey('f') || Game::instance().getKey('F') || Game::instance().getKey('2'))) {
		finishCooking = true;
		godModeInputsCD = ACTION_INTERVAL;
	}

	if (godModeInputsCD <= 0 && godMode && (Game::instance().getKey('b') || Game::instance().getKey('B') || Game::instance().getKey('3'))) {
		fireproof = !fireproof;
		godModeInputsCD = ACTION_INTERVAL;
	}

	if (godModeInputsCD <= 0 && godMode && (Game::instance().getKey('t') || Game::instance().getKey('T') || Game::instance().getKey('4'))) {
		theWorld = !theWorld;
		godModeInputsCD = ACTION_INTERVAL;
	}

	int nParticlesToSpawn = 3;
	ParticleSystem::Particle particle;

	if (walking) {
		particle.lifetime = 0.25f;
		for (int i = 0; i < nParticlesToSpawn; i++)
		{
			float z = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.1f - -2.f)));
			float x = -0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5f - -0.5f)));
			float xPrime = x * cos(rotation * PI / 180) - z * sin(rotation * PI / 180);
			float zPrime = z * cos(rotation * PI / 180) + x * sin(rotation * PI / 180);
			particle.position = glm::vec3(-xPrime, -1.5f, zPrime);
			particle.position += position;
			particle.speed = 1.5f * glm::normalize(0.5f * particle.position + glm::vec3(0.f, 3.f, 0.f));
			particles->addParticle(particle);
		}
	}
	particles->update(deltaTime / 1000.f);
}

std::vector<glm::vec3> Player::getFrontBBox()
{
	std::vector<glm::vec3> modelBbox = model->getBoundingBox();
	std::vector<glm::vec3> bbox;
	bbox.resize(2);
	bbox[0] = glm::vec3(modelBbox[0].x, 0.f, modelBbox[1].z);
	bbox[1] = glm::vec3(modelBbox[1].x, 0.f, modelBbox[1].z + 0.5f);

	//l'escalem
	bbox[0] *= scale; // model->getHeight();
	bbox[1] *= scale; // model->getHeight();

	//la rotem
	float xPrime = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
	float zPrime = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
	bbox[0].x = - xPrime;
	bbox[0].z = zPrime;
	xPrime = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
	zPrime = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);
	bbox[1].x = - xPrime;
	bbox[1].z = zPrime;

	//la desplacem a la posicio de l'entitat
	bbox[0] += position;
	bbox[1] += position;

	return bbox;
}

std::vector<glm::vec3> Player::getExtinguisherBBox()
{
	std::vector<glm::vec3> modelBbox = model->getBoundingBox();
	std::vector<glm::vec3> bbox;
	bbox.resize(2);
	bbox[0] = glm::vec3(modelBbox[0].x, 0.f, modelBbox[1].z);
	bbox[1] = glm::vec3(modelBbox[1].x, 0.f, modelBbox[1].z + 2.75f);

	//l'escalem
	bbox[0] *= scale;
	bbox[1] *= scale;

	//la rotem
	float xPrime = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
	float zPrime = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
	bbox[0].x = - xPrime;
	bbox[0].z = zPrime;
	xPrime = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
	zPrime = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);
	bbox[1].x = - xPrime;
	bbox[1].z = zPrime;

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
	if (holding != NULL) {
		adjustItemPosition();
	}
	walking = true;
}

bool Player::hold(Item * item)
{
	if (holdDropCD <= 0 && !cutting && Game::instance().getKey(' ')) {
		if (holding == NULL) {
			holding = item;
			
			adjustItemPosition();
			
			holdDropCD = ACTION_INTERVAL;
			return true;
		}
		else if (!holding->isFood() && item->isFood()) {
			return ((Tool*)holding)->addFood((Food*) item);
		}
	}
	return false;
}

void Player::dropHolding()
{
	if (holdDropCD <= 0) {
		if (holding->whatAmI() == "Extinguisher") {
			((Extinguisher*)holding)->stop();
		}
		if (level->putItemOnTable(holding) != Level::FULL) {
			holding = NULL;
			holdDropCD = ACTION_INTERVAL;
		}
	}
}

void Player::checkStartStopCutting()
{
	if (holding == NULL && startStopCutting <= 0 && (Game::instance().getKey('c') || Game::instance().getKey('C')) /*hauria de ser CTRL pero en GLUT no se pot*/) {
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

bool Player::holdingPlate()
{
	if (holding != NULL) {
		return holding->whatAmI() == "Plate";
	}
	return false;
}

bool Player::usingExtinguisher()
{
	if (holding != NULL && holding->whatAmI() == "Extinguisher") {
		return ((Extinguisher*)holding)->isActive();
	}
	return false;
}

bool Player::godModeOn()
{
	return godMode;
}

bool Player::checkFinishCooking()
{
	return finishCooking;
}

bool Player::fireproofOn()
{
	return fireproof;
}

bool Player::timeFrozen()
{
	return theWorld;
}

void Player::adjustItemPosition()
{
	glm::vec3 itemPosition = glm::vec3(0.f, 1.5f, 2.f);
	float xPrime = itemPosition.x * cos(rotation * PI / 180) - itemPosition.z * sin(rotation * PI / 180);
	float zPrime = itemPosition.z * cos(rotation * PI / 180) + itemPosition.x * sin(rotation * PI / 180);
	itemPosition.x = xPrime * -1;
	itemPosition.z = zPrime;
	itemPosition += position;
	holding->setPosition(glm::vec3(itemPosition));
	holding->setRotation(getRotation());
}
