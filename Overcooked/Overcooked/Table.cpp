#include "Table.h"
#include "Player.h"
#include "Tool.h"
#include "FryingPan.h"
#include "Pot.h"

#define PI 3.14159f

bool Table::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/EmptyTable.obj", program);
}

void Table::update(int deltaTime)
{
	if (this->item != NULL) {
		this->item->update(deltaTime);
		if (playerFacingThis() && player->hold(this->item))
			this->item = NULL;
		else if (!this->item->isFood() && this->item->whatAmI() != "Extinguisher"){
			bool toolFinished = ((Tool*)(this->item))->finished();
			bool playerFacingTable = playerFacingThis();
			bool playerHoldingPlate = player->holdingPlate();
			bool toolIsPot = this->item->whatAmI() == "Pot";
			bool toolIsPan = this->item->whatAmI() == "FryingPan";
			Food* finished = NULL;
			if (toolIsPot || toolIsPan)
				finished = ((Tool*)(this->item))->getFood();
			if (toolFinished &&
				playerFacingTable &&
				playerHoldingPlate &&
				player->hold(finished)) {

				((Tool*)(this->item))->empty();
			}
		}
	}
}

bool Table::setItem(Item * item)
{
	if (this->item == NULL) {
		item->setPosition(glm::vec3(position.x, 1.5f, position.z));
		item->setRotation(rotation);
		this->item = item;
		return true;
	}
	else if (this->item->whatAmI() == "Extinguisher") {
		return false;
	}
	else if (this->item->isFood() && !item->isFood()) {
		if (((Tool*)item)->addFood((Food*) this->item)) {
			item->setPosition(glm::vec3(position.x, 1.5f, position.z));
			item->setRotation(rotation);
			this->item = item;
			return true;
		}
	}
	else if (!this->item->isFood() && item->isFood()) {
		return ((Tool*) this->item)->addFood((Food*)item);
	}
	else if (!this->item->isFood() && !item->isFood()) {
		if (((Tool*)item)->hasFood()) {
			((Tool*) this->item)->addFood(((Tool*)item)->getFood());
			((Tool*)item)->empty();
		}
		return false;
	}
	return false;
}

bool Table::collisionWithPlayer()
{
	return inContactWithPlayer();
}

bool Table::playerFacingThis()
{
	std::vector<glm::vec3> bbox = getBoundingBox();
	std::vector<glm::vec3> playerBbox = player->getFrontBBox();

	//rotem la bbox de l'entitat

		//rotem respecte el 0,0
		bbox[0] -= position;
		bbox[1] -= position;

		float xPrime = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
		float zPrime = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
		bbox[0].x = xPrime;
		bbox[0].z = zPrime;
		xPrime = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
		zPrime = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);
		bbox[1].x = xPrime;
		bbox[1].z = zPrime;

		//tornem a la posicio
		bbox[0] += position;
		bbox[1] += position;

	glm::vec3 eTopRight = glm::vec3(bbox[0].x, 0.f, bbox[1].z);
	glm::vec3 eBotLeft = glm::vec3(bbox[1].x, 0.f, bbox[0].z);

	glm::vec3 pTopRight = glm::vec3(playerBbox[0].x, 0.f, playerBbox[1].z);
	glm::vec3 pBotLeft = glm::vec3(playerBbox[1].x, 0.f, playerBbox[0].z);

	//ignorem la y
	bbox[0].y = 0;
	bbox[1].y = 0;
	playerBbox[0].y = 0;
	playerBbox[1].y = 0;

	//reajustem quin punt es quin, de manera que bbox[0] es sempre el punt de baix a la dreta
	if (rotation >= 45.f && rotation < 135.f) {
		glm::vec3 bbox0aux = bbox[0];
		glm::vec3 bbox1aux = bbox[1];
		bbox[0] = eBotLeft;
		bbox[1] = eTopRight;
		eBotLeft = bbox0aux;
		eTopRight = bbox1aux;
	}
	else if (rotation >= 135.f && rotation < 225.f) {
		glm::vec3 bbox0aux = bbox[0];
		glm::vec3 BLaux = eBotLeft;
		bbox[0] = bbox[1];
		bbox[1] = bbox0aux;
		eBotLeft = eTopRight;
		eTopRight = BLaux;
	}
	else if (rotation >= 225.f && rotation < 315.f) {
		glm::vec3 bbox0aux = bbox[0];
		glm::vec3 bbox1aux = bbox[1];
		bbox[0] = eTopRight;
		bbox[1] = eBotLeft;
		eBotLeft = bbox0aux;
		eTopRight = bbox1aux;
	}

	bool en0InsidePlayer = glm::all(glm::greaterThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[0], playerBbox[1]));
	bool en1InsidePlayer = glm::all(glm::greaterThanEqual(bbox[1], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[1], playerBbox[1]));
	bool enTRInsidePlayer = glm::all(glm::greaterThanEqual(eTopRight, playerBbox[0])) && glm::all(glm::lessThanEqual(eTopRight, playerBbox[1]));
	bool enBLInsidePlayer = glm::all(glm::greaterThanEqual(eBotLeft, playerBbox[0])) && glm::all(glm::lessThanEqual(eBotLeft, playerBbox[1]));
	bool p0InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[0], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[0], bbox[1]));
	bool p1InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[1], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[1], bbox[1]));
	bool pTRInsideEntity = glm::all(glm::greaterThanEqual(pTopRight, bbox[0])) && glm::all(glm::lessThanEqual(pTopRight, bbox[1]));
	bool pBLInsideEntity = glm::all(glm::greaterThanEqual(pBotLeft, bbox[0])) && glm::all(glm::lessThanEqual(pBotLeft, bbox[1]));
	return en0InsidePlayer || en1InsidePlayer || enTRInsidePlayer || enBLInsidePlayer || p0InsideEntity || p1InsideEntity || pTRInsideEntity || pBLInsideEntity;
}
