#include "Table.h"
#include "Player.h"

bool Table::init(ShaderProgram & program)
{
	return loadFromFile("models/EmptyTable.obj", program);
}

void Table::setItem(Item * item)
{
	item->setPosition(glm::vec3(position.x, 1.2f, position.z));
	this->item = item;
}

bool Table::collisionWithPlayer()
{
	return inContactWithPlayer();
}

bool Table::playerFacingThis() //fem una trampeta
{
	std::vector<glm::vec3> bbox = getBoundingBox();
	std::vector<glm::vec3> playerBbox = player->getBoundingBox();

	playerBbox[0] -= 0.1f;
	playerBbox[1] += 0.1f;

	//ignorem la y
	bbox[0].y = 0;
	bbox[1].y = 0;
	playerBbox[0].y = 0;
	playerBbox[1].y = 0;

	bool en0InsidePlayer = glm::all(glm::greaterThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[0], playerBbox[1]));
	bool en1InsidePlayer = glm::all(glm::greaterThanEqual(bbox[1], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[1], playerBbox[1]));
	bool p0InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[0], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[0], bbox[1]));
	bool p1InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[1], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[1], bbox[1]));
	return en0InsidePlayer || en1InsidePlayer || p0InsideEntity || p1InsideEntity;
}
