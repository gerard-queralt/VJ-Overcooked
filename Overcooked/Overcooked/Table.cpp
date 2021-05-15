#include "Table.h"
#include "Player.h"
#include "Tool.h"
#include "Pot.h"

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
		else if (!this->item->isFood() &&
			this->item->whatAmI() == "Pot" &&
			((Pot*)(this->item))->finished() &&
			playerFacingThis() &&
			player->holdingPlate() &&
			player->hold(((Pot*)(this->item))->getFinishedRecipe())) {
			
			((Pot*)(this->item))->empty();
		}
	}
}

bool Table::setItem(Item * item)
{
	if (this->item == NULL) {
		item->setPosition(glm::vec3(position.x, 1.3f, position.z));
		this->item = item;
		return true;
	}
	else if (this->item->isFood() && !item->isFood()) {
		if (((Tool*)item)->addFood((Food*) this->item)) {
			item->setPosition(glm::vec3(position.x, 1.2f, position.z));
			this->item = item;
			return true;
		}
	}
	else if (!this->item->isFood() && item->isFood()) {
		((Tool*) this->item)->addFood((Food*)item);
		return true;
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

	bool en0InsidePlayer = glm::all(glm::greaterThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[0], playerBbox[1]));
	bool en1InsidePlayer = glm::all(glm::greaterThanEqual(bbox[1], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[1], playerBbox[1]));
	bool p0InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[0], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[0], bbox[1]));
	bool p1InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[1], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[1], bbox[1]));
	return en0InsidePlayer || en1InsidePlayer || p0InsideEntity || p1InsideEntity;
}
