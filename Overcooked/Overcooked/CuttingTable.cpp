#include "CuttingTable.h"

#include "Player.h"
#include "Onion.h"

#define CUTTING_TIME 500

bool CuttingTable::init(ShaderProgram & program)
{
	setScale(1.f);
	working = Billboard::createBillboard(glm::vec2(1.f, 1.f), program, "images/tmpHourglass.png");
	working->setType(BILLBOARD_Y_AXIS);
	return loadFromFile("models/CuttingTable.obj", program);
}

void CuttingTable::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (0 < cuttingTime && cuttingTime < CUTTING_TIME) {
		//render billboard, segurament necessitem una funcio a part
	}
	Entity::render(program, viewMatrix);
}

void CuttingTable::update(int deltaTime)
{
	Table::update(deltaTime);
	if (playerFacingThis())
		player->checkStartStopCutting();
	if (item != NULL && item->isFood() && !((Food*) item)->isCut() && playerFacingThis() && player->isCutting()) {
		cuttingTime += deltaTime;
		if (cuttingTime >= CUTTING_TIME) {
			((Onion*)item)->cut();
			cuttingTime = 0;
			player->stopCutting();
		}
	}
}
