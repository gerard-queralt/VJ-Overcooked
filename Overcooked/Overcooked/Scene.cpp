#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"

#include "LevelFactory.h"

#define PI 3.14159f

Scene::Scene()
{
	level = NULL;
	player = NULL;
	billboard = NULL;
}

Scene::~Scene()
{
	if (level != NULL)
		delete level;
	if (player != NULL)
		delete player;
	if (billboard != NULL)
		delete billboard;
}


void Scene::init()
{
	initShaders();
	level = LevelFactory::instance().createLevel(1, texProgram);
	player = new Player();
	player->init(texProgram);
	player->setPosition(glm::vec3(0.f, 0.f, -5.f));
	player->setLevel(level);

	level->setPlayer(player);

	billboard = Billboard::createBillboard(glm::vec2(1.f, 1.f), texProgram, "images/tmpHourglass.png");
	billboard->setType(BILLBOARD_CENTER);

	for (int i = 0; i < 2; ++i) {
		Number* n = new Number();
		n->init(glm::vec2(float(CAMERA_WIDTH) - 26.f * (i+2), float(CAMERA_HEIGHT) - 26.f * 2.f), texProgram);
		n->changeNumber(0);
		timeSprites.push_back(n);
	}

	timeSeparatorSpritesheet.loadFromFile("images/colon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeSeparator = Sprite::createSprite(glm::ivec2(26, 20), glm::vec2(1.f, 1.f), &timeSeparatorSpritesheet, &texProgram);
	timeSeparator->setPosition(glm::vec2(float(CAMERA_WIDTH) - 26.f * (4), float(CAMERA_HEIGHT) - 26.f * 2.f));

	for (int i = 2; i < 4; ++i) {
		Number* n = new Number();
		n->init(glm::vec2(float(CAMERA_WIDTH) - 26.f * (i + 3), float(CAMERA_HEIGHT) - 26.f * 2.f), texProgram);
		n->changeNumber(0);
		timeSprites.push_back(n);
	}

	// Initialize particle system
	//ParticleSystem::Particle particle;
	//particle.lifetime = 1e10f;
	//particles = new ParticleSystem();
	//particles->init(glm::vec2(0.5f, 0.5f), texProgram, "images/particle.png", 2.f);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	projection = glm::perspective(45.f / 180.f * PI, float(CAMERA_WIDTH) / float(CAMERA_HEIGHT), 0.1f, 100.f);
	projection2D = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	/*
	int nParticlesToSpawn = 20 * (int((currentTime + deltaTime) / 100.f) - int(currentTime / 100.f));
	ParticleSystem::Particle particle;
	float angle;

	particle.lifetime = 1.4f;
	for (int i = 0; i < nParticlesToSpawn; i++)
	{
		angle = 2.f * PI * (i + float(rand()) / RAND_MAX) / nParticlesToSpawn;
		particle.position = glm::vec3(cos(angle), -1.75f, sin(angle));
		particle.speed = 1.5f * glm::normalize(0.5f * particle.position + glm::vec3(0.f, 3.f, 0.f));
		particles->addParticle(particle);
	}
	*/
	currentTime += deltaTime;

	//particles->update(deltaTime / 1000.f);

	player->update(deltaTime);

	level->update(deltaTime);

	
}

void Scene::render()
{
	glm::mat4 modelMatrix, viewMatrix;
	glm::mat3 normalMatrix;

	texProgram.use();
	texProgram.setUniform1b("bLighting", true);
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 obs = glm::vec3(0.f, 32.f, -21.f);
	viewMatrix = glm::lookAt(obs, glm::vec3(0.f, 0.f, -(180.f * PI/180)), glm::vec3(0.f, 1.f, 0.f));

	// Render level
	modelMatrix = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
	normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
	texProgram.setUniformMatrix3f("normalmatrix", normalMatrix);
	level->render();

	//Render items
	level->renderEntities(texProgram, viewMatrix);

	// Render player
	player->render(texProgram, viewMatrix);



	texProgram.setUniformMatrix4f("projection", projection2D);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	for (int i = 0; i < timeSprites.size(); ++i) {
		timeSprites[i]->render();
	}
	timeSeparator->render();

	// Render billboard
	//texProgram.setUniform1b("bLighting", false);
	//modelMatrix = glm::mat4(1.0f);
	//texProgram.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
	//normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
	//texProgram.setUniformMatrix3f("normalmatrix", normalMatrix);
	//billboard->render(glm::vec3(8.f, 10.f, -16.f), glm::vec3(8.f, 32.f, -21.f));
	//billboard->render(glm::vec3(2.f, -1.5f, 0.f), obs);
	//billboard->render(glm::vec3(-2.f, -1.5f, 0.f), obs);
	//billboard->render(glm::vec3(0.f, -1.5f, 2.f), obs);
	//billboard->render(glm::vec3(0.f, -1.5f, -2.f), obs);

	// Render particles
	/*
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	modelMatrix = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);
	normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
	texProgram.setUniformMatrix3f("normalmatrix", normalMatrix);
	particles->render(obs);

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	*/
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



