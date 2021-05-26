#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

#include "Player.h"
#include "Table.h"
#include "Food.h"
#include "Sprite.h"

using namespace std;

// Class Level renders a very simple room with textures

class Level
{

public:
	// Levels can only be created inside an OpenGL context
	static Level *createLevel(const glm::vec3 &levelSize, ShaderProgram &program, const string &floorFile, const string &wallFile);

	Level(const glm::vec3 &levelSize, ShaderProgram &program, const string &floorFile, const string &wallFile);
	~Level();

	void render() const;
	void renderEntities(ShaderProgram texProgram, glm::mat4 viewMatrix);
	void update(int deltaTime);
	void free();

	glm::vec3 getSize();
	
	void addItem(Item* item);
	void removeItem(Item* item);
	void addTable(Table* table);
	void setPlayer(Player* player);

	bool playerCollision(Player* player);

	enum PutItemResult {
		NOT_TOUCHING = 0, FULL, SUCCESS
	};
	PutItemResult putItemOnTable(Item* item);

	enum PossibleRecipes {
		ONION_SOUP = 0, TOMATO_SOUP, MUSHROOM_SOUP, SALAD, BURGER, BURGER_CHEESE, BURGER_TOMATO, BURGER_LETTUCE, UNKNOWN
	};

	void addPossibleRecipe(PossibleRecipes recipe);
	void setTime(int minutes, int seconds);
	void setPoints(int points);
	int getMinutes();
	int getSeconds();
	int getPoints();
	int getPointsRequired();
	int getCurrentTime();

	bool deliver(Food* food);

	int getNumberPendingRecipes();
	Item* getNextPendingRecipe();

private:
	void prepareArrays(ShaderProgram &program);

	void askRandomRecipe();

private:
	GLuint vao[2];
	GLuint vbo[2];
	GLint posLocation[2], normalLocation[2], texCoordLocation[2];
	glm::vec3 size;
	Texture floor, wall;

	vector<Item *> items;
	vector<Table* > tables;

	ShaderProgram program;
	std::vector<PossibleRecipes> recipes;
	std::vector<std::vector<Item*> > pendingRecipes; //array on cada fila representa una recepta, la primera columna la recepta finalitzada i la resta els ingredients
	int timeSeconds;
	int timeMinutes;
	int pointsReq;
	int curPoints = 0;
	int currentTime;
	int nextRecipeTime;
};


#endif // _LEVEL_INCLUDE


