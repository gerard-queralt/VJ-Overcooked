#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "AssimpModel.h"
#include "Billboard.h"
#include "Number.h"
#include "Menu.h"

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
	void createLevel(int levelNum);

private:
	Level *level;
	Player *player;
	Billboard *billboard;
	
	std::vector<Number*> timeSprites;
	std::vector<Number*> pointsSprites;
	Sprite* timeSeparator;
	Texture timeSeparatorSpritesheet;
	int timeSeconds;
	int timeMinutes;
	int secondsIncrement = 0;
	int currentLevelTime;

	Sprite* timeText;
	Texture timeTextSpritesheet;
	Sprite* winText;
	Texture winTextSpritesheet;
	Sprite* loseText;
	Texture loseTextSpritesheet;
	Sprite* mainMenu;
	Texture mainMenuSpriteSheet;
	Sprite* levelMenu;
	Texture levelMenuSpriteSheet;
	Menu *arrow;
	int inputCd;

	int currentState;

	bool timeUp = false;

	Sprite* recipeOutline;
	Texture recipeOutlineSpritesheet;
	
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection, projection2D;
};


#endif // _SCENE_INCLUDE

