#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

#include "Player.h"

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
	void renderItems(ShaderProgram texProgram, glm::mat4 viewMatrix);
	void update(int deltaTime);
	void free();

	glm::vec3 getSize();
	
	void addEntity(Entity* entity);
	void setPlayer(Player* player);

private:
	void prepareArrays(ShaderProgram &program);

private:
	GLuint vao[2];
	GLuint vbo[2];
	GLint posLocation[2], normalLocation[2], texCoordLocation[2];
	glm::vec3 size;
	Texture floor, wall;

	vector<Entity *> entities;
};


#endif // _LEVEL_INCLUDE


