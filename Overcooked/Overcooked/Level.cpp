#include <iostream>
#include <vector>
#include "Level.h"
#include "Plate.h"
#include "OnionSoup.h"
#include "Onion.h"
#include "TomatoSoup.h"
#include "Tomato.h"
#include "MushroomSoup.h"
#include "Mushroom.h"
#include "Salad.h"
#include "Lettuce.h"
#include "Burger.h"
#include "Beef.h"
#include "Bread.h"

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
	this->program = program;
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
	for (std::vector<Item*> recipe : pendingRecipes) {
		for (Item* i : recipe) {
			i->render(texProgram, viewMatrix);
		}
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
	if (pendingRecipes.size() < 6) {
		askRandomRecipe();
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

void Level::removeItem(Item * item)
{
	items.erase(std::remove(items.begin(), items.end(), item));
	delete item;
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

Level::PutItemResult Level::putItemOnTable(Item * item)
{
	for (Table* t : tables) {
		if (t->playerFacingThis()) {
			if (t->setItem(item))
				return SUCCESS;
			else
				return FULL;
		}
	}
	return NOT_TOUCHING;
}

void Level::addPossibleRecipe(PossibleRecipes recipe)
{
	recipes.push_back(recipe);
}

void Level::setTime(int minutes, int seconds)
{
	timeMinutes = minutes;
	timeSeconds = seconds;
}

void Level::setPoints(int points)
{
	pointsReq = points;
}

int Level::getMinutes()
{
	return timeMinutes;
}

int Level::getSeconds()
{
	return timeSeconds;
}

int Level::getPoints()
{
	return curPoints;
}

int Level::getPointsRequired()
{
	return pointsReq;
}

bool Level::deliver(Food * food)
{
	if (food->whatAmI() == "OnionSoup"
		|| food->whatAmI() == "MushroomSoup"
		|| food->whatAmI() == "TomatoSoup"
		|| food->whatAmI() == "Burger"
		|| food->whatAmI() == "Salad") {

		PossibleRecipes recipe = UNKNOWN;
		if (food->whatAmI() == "OnionSoup") {
			recipe = ONION_SOUP;
		}
		else if (food->whatAmI() == "MushroomSoup") {
			recipe = MUSHROOM_SOUP;
		}
		else if (food->whatAmI() == "TomatoSoup") {
			recipe = TOMATO_SOUP;
		}
		else if (food->whatAmI() == "Salad") {
			recipe = SALAD;
		}
		else if (food->whatAmI() == "BURGER") {
			switch (((Burger*)food)->getTopping()) {
			case Burger::NOTHING:
				recipe = BURGER;
				break;
			case Burger::CHEESE:
				recipe = BURGER_CHEESE;
				break;
			case Burger::TOMATO:
				recipe = BURGER_TOMATO;
				break;
			case Burger::LETTUCE:
				recipe = BURGER_LETTUCE;
				break;
			default:
				break;
			}
		}

		for (PossibleRecipes r : recipes) {
			if (r == recipe) {
				curPoints += 150;
				break;
			}
		}

		return true;
	}
	return false;
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

void Level::askRandomRecipe()
{
	int randomRecipe = (rand() % static_cast<int>(recipes.size()));
	PossibleRecipes recipe = recipes[randomRecipe];
	switch (recipe)
	{
	case Level::ONION_SOUP:
	{
		std::vector<Item*> recipeModels;
		Plate* plate = new Plate();
		plate->init(program);
		plate->addFood(new OnionSoup());
		plate->setPosition(glm::vec3(23.5f - pendingRecipes.size() * 7.f, 5.f, 16.f));
		recipeModels.push_back(plate);
		for (int o = 0; o < 3; ++o) {
			Onion* onion = new Onion();
			onion->init(program);
			onion->setPosition(glm::vec3(25.f - 2.f * o - pendingRecipes.size() * 7.f, 5.f, 13.5f));
			recipeModels.push_back(onion);
		}
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::TOMATO_SOUP:
		break;
	case Level::MUSHROOM_SOUP:
		break;
	case Level::SALAD:
		break;
	case Level::BURGER:
		break;
	case Level::BURGER_CHEESE:
		break;
	case Level::BURGER_TOMATO:
		break;
	case Level::BURGER_LETTUCE:
		break;
	case Level::UNKNOWN:
		break;
	default:
		break;
	}
}






























