#include "CuttingTable.h"

#include "Player.h"
#include "Onion.h"

bool CuttingTable::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/CuttingTable.obj", program);
}

void CuttingTable::update(int deltaTime)
{
	Table::update(deltaTime);
	if (item != NULL && item->isFood() && !((Food*) item)->isCut()) {
		((Onion*)item)->cut();
		item->setPosition(glm::vec3(position.x, 1.2f, position.z));
	}
}
