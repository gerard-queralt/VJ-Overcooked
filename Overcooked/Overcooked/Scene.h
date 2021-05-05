#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "AssimpModel.h"
#include "Billboard.h"
#include "ParticleSystem.h"


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

	enum PlayerDirections {
		FRONT = 0, BACK, LEFT, RIGHT
	};

	enum CameraTypes {
		FP = 0, TP, CAM_1, CAM_2, CAM_3, CAM_4
	};

	void movePlayer(int dir);

	void changeCamera(int newCam);

private:
	void initShaders();

private:
	Level *level;
	AssimpModel *model;
	Billboard *billboard;
	ParticleSystem *particles;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	int camera;
};


#endif // _SCENE_INCLUDE

