#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

#include "Player.h"
#include "Table.h"
#include "Food.h"

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

	void setTime(int minutes, int seconds);
	void setPoints(int points);
	int getMinutes();
	int getSeconds();
	int getPoints();

	bool deliver(Food* food);

private:
	void prepareArrays(ShaderProgram &program);

private:
	GLuint vao[2];
	GLuint vbo[2];
	GLint posLocation[2], normalLocation[2], texCoordLocation[2];
	glm::vec3 size;
	Texture floor, wall;

	vector<Item *> items;
	vector<Table* > tables;

	int timeSeconds;
	int timeMinutes;
	int pointsReq;
	int curPoints = 0;
};


#endif // _LEVEL_INCLUDE


