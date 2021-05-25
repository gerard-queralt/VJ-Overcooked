#include "Extinguisher.h"

#define PI 3.14159f //temporal

bool Extinguisher::init(ShaderProgram & program)
{
	setScale(2.f);

	inUse = false;
	// Initialize particle system
	ParticleSystem::Particle particle;
	particle.lifetime = 1e10f;
	particles = new ParticleSystem();
	particles->init(glm::vec2(1.f, 1.f), program, "images/dust.png", 2.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return loadFromFile("models/Extinguisher.obj", program);
}

void Extinguisher::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	Entity::render(program, viewMatrix);
	if (inUse) {
		//render particles
		glm::mat4 modelMatrix;
		glm::mat3 normalMatrix;
		glm::vec3 obs = glm::vec3(0.f, 36.f, -24.f);
		program.setUniform1b("bLighting", false);

		glEnable(GL_BLEND);

		modelMatrix = glm::mat4(1.0f);
		program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
		program.setUniformMatrix3f("normalmatrix", normalMatrix);
		program.setUniform2f("texCoordDispl", 0.f, 0.f);
		particles->render(obs);

		glDisable(GL_BLEND);
		program.setUniform1b("bLighting", true);
	}
}

void Extinguisher::update(int deltaTime)
{
	Item::update(deltaTime);

	int nParticlesToSpawn = 3;
	ParticleSystem::Particle particle;

	particle.lifetime = 0.1f;
	for (int i = 0; i < nParticlesToSpawn; i++)
	{
		float z = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - 0.5f)));
		float x = -0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5f - -0.5f)));
		float xPrime = x * cos(rotation * PI / 180) - z * sin(rotation * PI / 180);
		float zPrime = z * cos(rotation * PI / 180) + x * sin(rotation * PI / 180);
		float y = -1.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5f - -1.5f)));
		particle.position = glm::vec3(-xPrime, y, zPrime);
		particle.position += position;
		particle.speed = 1.5f * glm::normalize(0.5f * particle.position + glm::vec3(0.f, 3.f, 0.f));
		particles->addParticle(particle);
	}
	particles->update(deltaTime / 1000.f);
}

void Extinguisher::changeState()
{
	inUse = !inUse;
}

bool Extinguisher::isActive()
{
	return inUse;
}

void Extinguisher::stop()
{
	inUse = false;
}

bool Extinguisher::isFood()
{
	return false;
}

string Extinguisher::whatAmI()
{
	return "Extinguisher";
}
