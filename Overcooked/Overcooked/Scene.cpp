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
		timeSprites.push_back(n);
	}

	timeSeparatorSpritesheet.loadFromFile("images/colon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeSeparator = Sprite::createSprite(glm::ivec2(26, 20), glm::vec2(1.f, 1.f), &timeSeparatorSpritesheet, &texProgram);
	timeSeparator->setPosition(glm::vec2(float(CAMERA_WIDTH) - 26.f * (4), float(CAMERA_HEIGHT) - 26.f * 2.f));

	for (int i = 2; i < 4; ++i) {
		Number* n = new Number();
		n->init(glm::vec2(float(CAMERA_WIDTH) - 26.f * (i + 3), float(CAMERA_HEIGHT) - 26.f * 2.f), texProgram);
		timeSprites.push_back(n);
	}

	Number* n = new Number();
	n->init(glm::vec2(26.f, float(CAMERA_HEIGHT) - 26.f * 2.f), texProgram);
	n->changeNumber(0);
	pointsSprites.push_back(n);

	timeTextSpritesheet.loadFromFile("images/time!.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeText = Sprite::createSprite(glm::ivec2(160, 32), glm::vec2(1.f, 1.f), &timeTextSpritesheet, &texProgram);
	timeText->setPosition(glm::vec2(7.5f * 32.f, 6.f * 32.f));

	winTextSpritesheet.loadFromFile("images/win.png", TEXTURE_PIXEL_FORMAT_RGBA);
	winText = Sprite::createSprite(glm::ivec2(96, 32), glm::vec2(1.f, 1.f), &winTextSpritesheet, &texProgram);
	winText->setPosition(glm::vec2(8.5f * 32.f, 7.5f * 32.f));
	loseTextSpritesheet.loadFromFile("images/lose.png", TEXTURE_PIXEL_FORMAT_RGBA);
	loseText = Sprite::createSprite(glm::ivec2(128, 32), glm::vec2(1.f, 1.f), &loseTextSpritesheet, &texProgram);
	loseText->setPosition(glm::vec2(8.f * 32.f, 7.5f * 32.f));

	projection = glm::perspective(45.f / 180.f * PI, float(CAMERA_WIDTH) / float(CAMERA_HEIGHT), 0.1f, 100.f);
	projection2D = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
	timeMinutes = level->getMinutes();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);

	level->update(deltaTime);

	timeSeconds = level->getSeconds() - (int(currentTime) / 1000) % 60 + secondsIncrement;
	if (timeSeconds < 0) {
		secondsIncrement += 60;
		timeSeconds += 60;
		--timeMinutes;
	}
	else if (timeSeconds >= 60) {
		secondsIncrement -= 60;
		timeSeconds -= 60;
	}
	if (timeMinutes < 0) {
		timeUp = true;
	}
	else {
		timeSprites[0]->changeNumber(timeSeconds % 10);
		timeSprites[1]->changeNumber(timeSeconds / 10);
		timeSprites[2]->changeNumber(timeMinutes % 10);
		timeSprites[3]->changeNumber(timeMinutes / 10);
	}

	int points = level->getPoints();
	if (points > 0) {
		pointsSprites.clear();
		while (points > 0) {
			for (int p = 0; p < pointsSprites.size(); ++p) {
				pointsSprites[p]->setPosition(glm::vec2(26.f * (pointsSprites.size() - p + 1), float(CAMERA_HEIGHT) - 26.f * 2.f));
			}
			Number* n = new Number();
			n->init(glm::vec2(26.f, float(CAMERA_HEIGHT) - 26.f * 2.f), texProgram);
			n->changeNumber(points % 10);
			pointsSprites.push_back(n);
			points /= 10;
		}
	}
}

void Scene::render()
{
	glm::mat4 modelMatrix, viewMatrix;
	glm::mat3 normalMatrix;

	texProgram.use();
	texProgram.setUniform1b("bLighting", true);
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	glm::vec3 obs = glm::vec3(0.f, 36.f, -24.f);
	viewMatrix = glm::lookAt(obs, glm::vec3(0.f, 0.f, -(90.f * PI/180)), glm::vec3(0.f, 1.f, 0.f));

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

	// Render HUD

	texProgram.setUniformMatrix4f("projection", projection2D);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	for (int i = 0; i < timeSprites.size(); ++i) {
		timeSprites[i]->render();
	}
	timeSeparator->render();
	for (int i = pointsSprites.size() - 1; i >= 0; --i) {
		pointsSprites[i]->render();
	}

	if (timeUp) {
		timeText->render();
		if (level->getPoints() >= level->getPointsRequired())
			winText->render();
		else
			loseText->render();
	}
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



