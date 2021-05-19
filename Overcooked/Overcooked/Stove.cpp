#include "Stove.h"
#include "Tool.h"

#define PI 3.14159f

bool Stove::init(ShaderProgram & program)
{
	setScale(1.f);

	working = Billboard::createBillboard(glm::vec2(1.f, 1.f), program, "images/tmpHourglass.png");
	working->setType(BILLBOARD_Y_AXIS);

	// Initialize particle system
	ParticleSystem::Particle particle;
	particle.lifetime = 1e10f;
	particles = new ParticleSystem();
	particles->init(glm::vec2(0.5f, 0.5f), program, "images/particle.png", 2.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return loadFromFile("models/Stove.obj", program);
}

void Stove::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (this->item != NULL && !item->isFood()) {
		if (0 < ((Tool*) item)->getCookingTime() && ((Tool*)item)->getCookingTime() < COOKING_TIME) {
			glm::mat4 modelMatrix;
			glm::mat3 normalMatrix;
			glm::vec3 obs = glm::vec3(0.f, 32.f, -21.f);

			//render billboard
			program.setUniform1b("bLighting", false);
			modelMatrix = glm::mat4(1.0f);
			program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
			normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
			program.setUniformMatrix3f("normalmatrix", normalMatrix);
			working->render(glm::vec3(position.x, 1.f, position.z), obs);

			//render particles
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);

			modelMatrix = glm::mat4(1.0f);
			program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
			normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
			program.setUniformMatrix3f("normalmatrix", normalMatrix);
			particles->render(obs);

			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
			program.setUniform1b("bLighting", true);
		}
	}
	Entity::render(program, viewMatrix);
}

void Stove::update(int deltaTime)
{
	Table::update(deltaTime);
	if (item != NULL && ((Tool*)item)->hasFood()) {
		((Tool*)item)->cookFood(deltaTime);
	}

	/* MILLORAR!!!
	int nParticlesToSpawn = 10;
	ParticleSystem::Particle particle;
	float angle;

	particle.lifetime = 1.4f;
	for (int i = 0; i < nParticlesToSpawn; i++)
	{
		angle = 2.f * PI * (i + float(rand()) / RAND_MAX) / nParticlesToSpawn;
		particle.position = position + glm::vec3(0.f, 1.5f, 0.f);
		particle.speed = - (1.5f * glm::normalize(0.5f * particle.position + glm::vec3(0.f, 3.f, 0.f)));
		particles->addParticle(particle);
	}
	particles->update(deltaTime / 1000.f);
	*/
}

bool Stove::setItem(Item * item)
{
	if (this->item == NULL && !item->isFood()) {
		item->setPosition(glm::vec3(position.x, 1.2f, position.z));
		this->item = item;
		return true;
	}
	else if (this->item != NULL && !this->item->isFood() && item->isFood()) {
		return ((Tool*) this->item)->addFood((Food*)item);
	}
	return false;
}
