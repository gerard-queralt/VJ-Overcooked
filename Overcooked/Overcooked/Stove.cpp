#include "Stove.h"
#include "Tool.h"

#define PI 3.14159f

#define FLASH_TIME 10

bool Stove::init(ShaderProgram & program)
{
	setScale(1.f);

	working = Billboard::createBillboard(glm::vec2(1.f, 1.f), program, "images/tmpHourglass.png");
	working->setType(BILLBOARD_Y_AXIS);

	fireHazard = Billboard::createBillboard(glm::vec2(1.f, 1.f), program, "images/fireHazard.png");
	fireHazard->setType(BILLBOARD_Y_AXIS);
	fireHazardFlashTime = FLASH_TIME;

	// Initialize particle system
	ParticleSystem::Particle particle;
	particle.lifetime = 1e10f;
	particles = new ParticleSystem();
	particles->init(glm::vec2(1.f, 1.f), program, "images/fire.png", 2.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return loadFromFile("models/Stove.obj", program);
}

void Stove::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	Entity::render(program, viewMatrix);
	if (this->item != NULL && !item->isFood()) {
		if (0 < ((Tool*) item)->getCookingTime()) {
			glm::mat4 modelMatrix;
			glm::mat3 normalMatrix;
			glm::vec3 obs = glm::vec3(0.f, 32.f, -21.f);
			program.setUniform1b("bLighting", false);

			if (((Tool*)item)->getCookingTime() < COOKING_TIME) {
				//render billboard
				modelMatrix = glm::mat4(1.0f);
				program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
				normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
				program.setUniformMatrix3f("normalmatrix", normalMatrix);
				working->render(glm::vec3(position.x, 2.f, position.z), obs);
			}
			else if (((Tool*)item)->getCookingTime() - COOKING_TIME >= (BURN_TIME - COOKING_TIME) / 2 && ((Tool*)item)->getCookingTime() < BURN_TIME) {
				if (fireHazardFlashTime >= FLASH_TIME) {
					//render billboard
					modelMatrix = glm::mat4(1.0f);
					program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
					normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
					program.setUniformMatrix3f("normalmatrix", normalMatrix);
					fireHazard->render(glm::vec3(position.x, 2.f, position.z), obs);

					if (fireHazardFlashTime == FLASH_TIME * 2) {
						fireHazardFlashTime = 0;
					}
					else {
						++fireHazardFlashTime;
					}
				}
				else
					++fireHazardFlashTime;
			}

			//render particles
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
	}
}

void Stove::update(int deltaTime)
{
	Table::update(deltaTime);
	if (item != NULL && ((Tool*)item)->hasFood()) {
		((Tool*)item)->cookFood(deltaTime);
	}

	int nParticlesToSpawn = 5;
	if (item != NULL && ((Tool*)item)->getCookingTime() >= BURN_TIME) {
		nParticlesToSpawn *= 2;
	}
	ParticleSystem::Particle particle;
	float angle;

	particle.lifetime = 0.1f;
	for (int i = 0; i < nParticlesToSpawn; i++)
	{
		angle = 2.f * PI * (i + float(rand()) / RAND_MAX) / nParticlesToSpawn;
		float extraX = 0.f;
		float extraZ = 0.f;
		if (item != NULL && ((Tool*)item)->getCookingTime() >= BURN_TIME) {
			extraX = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
			extraZ = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
			particle.lifetime = 0.5f;
		}
		particle.position = glm::vec3(cos(angle) + extraX, -1.75f + 1.2f, sin(angle) + extraZ);
		particle.position += position;
		particle.speed = 1.5f * glm::normalize(0.5f * particle.position + glm::vec3(0.f, 3.f, 0.f));
		particles->addParticle(particle);
	}
	particles->update(deltaTime / 1000.f);
}

bool Stove::setItem(Item * item)
{
	if (this->item == NULL && !item->isFood()) {
		item->setPosition(glm::vec3(position.x, 1.5f, position.z));
		this->item = item;
		return true;
	}
	else if (this->item != NULL && !this->item->isFood() && item->isFood()) {
		return ((Tool*) this->item)->addFood((Food*)item);
	}
	return false;
}
