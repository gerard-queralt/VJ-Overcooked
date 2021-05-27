#include "Tool.h"
#include "Player.h"

void Tool::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (0 < cookingTime && cookingTime < COOKING_TIME) {
		glm::mat4 modelMatrix;
		glm::mat3 normalMatrix;
		glm::vec3 obs = glm::vec3(0.f, 36.f, -24.f);

		program.setUniform1b("bLighting", false);
		modelMatrix = glm::mat4(1.0f);
		program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
		program.setUniformMatrix3f("normalmatrix", normalMatrix);

		float percent = ((float)cookingTime) / ((float)COOKING_TIME) * 100;
		string path = "images/progress" + std::to_string((int)(percent / 10)) + ".png";
		working = Billboard::createBillboard(glm::vec2(1.f, 0.5f), program, path);
		working->setType(BILLBOARD_Y_AXIS);

		working->render(glm::vec3(position.x, 1.f, position.z), obs);

		program.setUniform1b("bLighting", true);
	}
	Entity::render(program, viewMatrix);
}

void Tool::cookFood(int deltaTime)
{
	cookingTime += deltaTime;
	
	if (player->checkFinishCooking() || (player->fireproofOn() && cookingTime > COOKING_TIME)) {
		cookingTime = COOKING_TIME;
	}

	if (COOKING_TIME <= cookingTime && cookingTime < BURN_TIME && !cookedUpdated) {
		cookedFood = true;
		cookedUpdated = true;
	}
	else if (BURN_TIME <= cookingTime && !burnedUpdated) {
		burnedFood = true;
		burnedUpdated = true;
	}
}

bool Tool::isFood()
{
	return false;
}

int Tool::getCookingTime()
{
	return cookingTime;
}

bool Tool::finished()
{
	return false;
}

Food * Tool::getFood()
{
	return NULL;
}
