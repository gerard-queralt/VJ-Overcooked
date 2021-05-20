#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "AssimpModel.h"
#include "Billboard.h"
#include "ParticleSystem.h"
#include "Number.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	Level *level;
	Player *player;
	Billboard *billboard;
	std::vector<Number*> timeSprites;
	Sprite* timeSeparator;
	Texture timeSeparatorSpritesheet;
	int timeSeconds;
	int timeMinutes;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection, projection2D;
};


#endif // _SCENE_INCLUDE

