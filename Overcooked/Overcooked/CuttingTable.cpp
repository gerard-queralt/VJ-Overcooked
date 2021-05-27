#include "CuttingTable.h"

#include "Player.h"
#include "Onion.h"

#include "Music.h"

#define CUTTING_TIME 500

bool CuttingTable::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/CuttingTable.obj", program);
}

void CuttingTable::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (0 < cuttingTime && cuttingTime < CUTTING_TIME) {
		glm::mat4 modelMatrix;
		glm::mat3 normalMatrix;
		glm::vec3 obs = glm::vec3(0.f, 36.f, -24.f);

		program.setUniform1b("bLighting", false);
		modelMatrix = glm::mat4(1.0f);
		program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
		program.setUniformMatrix3f("normalmatrix", normalMatrix);
		
		float percent = ((float)cuttingTime) / ((float)CUTTING_TIME) * 100;
		string path = "images/progress" + std::to_string((int)(percent / 10)) + ".png";
		working = Billboard::createBillboard(glm::vec2(1.f, 0.5f), program, path);
		working->setType(BILLBOARD_Y_AXIS);

		working->render(glm::vec3(position.x, 1.f, position.z), obs);
		
		program.setUniform1b("bLighting", true);
	}
		if (playerFacingThis() && !facingUpdated) {
		loadFromFile("models/CuttingTableSoft.obj", program);
		facingUpdated = true;
		notFacingUpdated = false;
	}
		else if(!playerFacingThis() && !notFacingUpdated){
		loadFromFile("models/CuttingTable.obj", program);
		notFacingUpdated = true;
		facingUpdated = false;
	}
	Entity::render(program, viewMatrix);
}

void CuttingTable::update(int deltaTime)
{
	Table::update(deltaTime);
	if (item != NULL && playerFacingThis() && !((Food*)item)->isCut())
		player->checkStartStopCutting();
	if (item != NULL && item->isFood() && !((Food*) item)->isCut() && playerFacingThis() && player->isCutting()) {
		if (!playingSound) {
			Music::instance().playSoundEffect(1);
			playingSound = true;
		}
		
		cuttingTime += deltaTime;
		if (cuttingTime >= CUTTING_TIME) {
			((Food*)item)->cut();
			cuttingTime = 0;
			player->stopCutting();
		}
	}
	else if(playingSound){
		Music::instance().stopSoundEffect(1);
		playingSound = false;
	}
}
