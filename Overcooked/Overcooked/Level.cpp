#include <iostream>
#include <vector>
#include "Level.h"

using namespace std;

Level *Level::createLevel(const glm::vec3 &levelSize, ShaderProgram &program, const string &floorFile, const string &wallFile)
{
	Level *level = new Level(levelSize, program, floorFile, wallFile);
	
	return level;
}


Level::Level(const glm::vec3 &levelSize, ShaderProgram &program, const string &floorFile, const string &wallFile)
{
	size = levelSize;
	if(!floor.loadFromFile(floorFile.c_str(), TEXTURE_PIXEL_FORMAT_RGB))
		cout << "Could not load floor texture!!!" << endl;
	if(!wall.loadFromFile(wallFile.c_str(), TEXTURE_PIXEL_FORMAT_RGB))
		cout << "Could not load wall texture!!!" << endl;
	prepareArrays(program);
}

Level::~Level()
{
}


void Level::render() const
{
	glEnable(GL_TEXTURE_2D);

	floor.use();
	glBindVertexArray(vao[0]);
	glEnableVertexAttribArray(posLocation[0]);
	glEnableVertexAttribArray(normalLocation[0]);
	glEnableVertexAttribArray(texCoordLocation[0]);
	glDrawArrays(GL_QUADS, 0, 4);

	wall.use();
	glBindVertexArray(vao[1]);
	glEnableVertexAttribArray(posLocation[1]);
	glEnableVertexAttribArray(normalLocation[1]);
	glEnableVertexAttribArray(texCoordLocation[1]);
	glDrawArrays(GL_QUADS, 0, 4 * 4);

	glDisable(GL_TEXTURE_2D);
}

void Level::renderEntities(ShaderProgram texProgram, glm::mat4 viewMatrix)
{
	for (Item* i : items) {
		i->render(texProgram, viewMatrix);
	}
	for (Table* t : tables) {
		t->render(texProgram, viewMatrix);
	}
}

void Level::update(int deltaTime)
{
	for (Item* i : items) {
		i->update(deltaTime);
	}
	for (Table* t : tables) {
		t->update(deltaTime);
	}
}

void Level::free()
{
	glDeleteBuffers(1, &vbo[0]);
	glDeleteVertexArrays(1, &vao[0]);
	
	glDeleteBuffers(1, &vbo[1]);
	glDeleteVertexArrays(1, &vao[1]);
}

glm::vec3 Level::getSize()
{
	return size;
}

void Level::addItem(Item * item)
{
	items.push_back(item);
}

void Level::addTable(Table * table)
{
	tables.push_back(table);
}

void Level::setPlayer(Player * player)
{
	for (Item* i : items) {
		i->setPlayer(player);
	}
	for (Table* t : tables) {
		t->setPlayer(player);
	}
}

bool Level::playerCollision(Player * player)
{
	std::vector<glm::vec3> bbox = player->getBoundingBox();
	
	if (bbox[0].x >= getSize().x / 2 || bbox[1].x >= getSize().x / 2)
		return true;
	if (bbox[0].z >= getSize().z / 2 || bbox[1].z >= getSize().z / 2)
		return true;
	if (bbox[0].x <= -getSize().x / 2 || bbox[1].x <= -getSize().x / 2)
		return true;
	if (bbox[0].z <= -getSize().z / 2 || bbox[1].z <= -getSize().z / 2)
		return true;
	for (Table* t : tables) {
		if (t->collisionWithPlayer())
			return true;
	}
	return false;
}

void Level::putItemOnTable(Item * item)
{
	for (Table* t : tables) {
		if (t->playerFacingThis()) {
			t->setItem(item);
			break;
		}
	}
}

void Level::prepareArrays(ShaderProgram &program)
{
	vector<float> vertices;

	// Floor
	vertices.push_back(-size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(1.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	vertices.push_back(-size.x/2.f);  vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(1.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(size.z / 4.f);

	vertices.push_back(size.x/2.f);  vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(1.f); vertices.push_back(0.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(size.z / 4.f);

	vertices.push_back(size.x/2.f);  vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(1.f); vertices.push_back(0.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(0.f);

	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation[0] = program.bindVertexAttribute("position", 3, 8*sizeof(float), 0);
	normalLocation[0] = program.bindVertexAttribute("normal", 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	texCoordLocation[0] = program.bindVertexAttribute("texCoord", 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));

	vertices.clear();
	// Front wall
	vertices.push_back(-size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	vertices.push_back(size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(0.f);

	vertices.push_back(size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(-size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(0.f); vertices.push_back(size.y / 4.f);

	// Back wall
	vertices.push_back(-size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(-1.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	vertices.push_back(-size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(-1.f);
	vertices.push_back(0.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(-1.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(0.f); vertices.push_back(0.f); vertices.push_back(-1.f);
	vertices.push_back(size.x / 4.f); vertices.push_back(0.f);

	// Left wall
	vertices.push_back(-size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	vertices.push_back(-size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(-size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(size.z / 4.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(-size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(size.z / 4.f); vertices.push_back(0.f);

	// Right wall
	vertices.push_back(size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(-1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	vertices.push_back(size.x/2.f); vertices.push_back(-size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(-1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(size.z / 4.f); vertices.push_back(0.f);

	vertices.push_back(size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(size.z/2.f);
	vertices.push_back(-1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(size.z / 4.f); vertices.push_back(size.y / 4.f);

	vertices.push_back(size.x/2.f); vertices.push_back(size.y/2.f); vertices.push_back(-size.z/2.f);
	vertices.push_back(-1.f); vertices.push_back(0.f); vertices.push_back(0.f);
	vertices.push_back(0.f); vertices.push_back(size.y / 4.f);

	glGenVertexArrays(1, &vao[1]);
	glBindVertexArray(vao[1]);
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * 32 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation[1] = program.bindVertexAttribute("position", 3, 8*sizeof(float), 0);
	normalLocation[1] = program.bindVertexAttribute("normal", 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	texCoordLocation[1] = program.bindVertexAttribute("texCoord", 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
}






























