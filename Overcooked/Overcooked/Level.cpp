#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
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
#include "Cheese.h"

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
	currentTime = 0;
	nextRecipeTime = 0;
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
	glClear(GL_DEPTH_BUFFER_BIT);
	for (std::vector<Item*> recipe : pendingRecipes) {
		for (Item* i : recipe) {
			i->render(texProgram, viewMatrix);
		}
	}
}

void Level::update(int deltaTime)
{
	currentTime += deltaTime;

	for (Item* i : items) {
		i->update(deltaTime);
	}
	for (Table* t : tables) {
		t->update(deltaTime);
	}
	if (nextRecipeTime <= 0 && pendingRecipes.size() < 6) {
		askRandomRecipe();
		nextRecipeTime = 15000; //uns 15 segons
	}
	else {
		nextRecipeTime -= deltaTime;
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

int Level::getCurrentTime()
{
	return currentTime;
}

bool Level::deliver(Food * food)
{
	if (food->whatAmI() == "OnionSoup"
		|| food->whatAmI() == "MushroomSoup"
		|| food->whatAmI() == "TomatoSoup"
		|| food->whatAmI() == "Burger"
		|| food->whatAmI() == "Salad") {

		int pos = 0;
		bool correct = false;
		while (pos < pendingRecipes.size() && !correct) {
			Item* current = pendingRecipes[pos][0];
			if (!current->isFood()) { //Sopes, on el primer element es el plat
				Food* r = ((Plate*)current)->getFood();
				if (food->whatAmI() == r->whatAmI()) {
					correct = true;
				}
			}
			else { //Ensalada i hamburguesa
				if (food->whatAmI() == current->whatAmI()) {
					if (food->whatAmI() == "Salad" || ((Burger*)food)->getTopping() == ((Burger*)current)->getTopping()) {
						correct = true;
					}
				}
			}
			++pos;
		}
		if (correct) {
			curPoints += 150;
			--pos;
			pendingRecipes.erase(pendingRecipes.begin() + pos);
			for (int i = pos; i < pendingRecipes.size(); ++i) {
				pendingRecipes[i][0]->setPosition(glm::vec3(24.5 - i * 8.75f, 5.f, 21.f));
				if (pendingRecipes[i].size() == 4) { // tres ingredients
					for (int j = 0; j < 3; ++j) {
						pendingRecipes[i][j+1]->setPosition(glm::vec3(25.5f - 2.f * j - i * 8.25f, 5.f, 18.f));
					}
				}
				else { // dos ingredients
					for (int j = 0; j < 2; ++j) {
						pendingRecipes[i][j + 1]->setPosition(glm::vec3(24.5f - j * 2.5f - i * 8.25f, 5.f, 18.f));
					}
				}
			}
		}
		return true;
	}
	return false;
}

int Level::getNumberPendingRecipes()
{
	return pendingRecipes.size();
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
	glm::vec3 recipePos = glm::vec3(24.5, 5.f, 21.f);
	float recipeXOffset = 8.75f;
	glm::vec3 ingredientOfThreePos = glm::vec3(25.5f, 5.f, 18.f);
	float ingredientOfThreeSpacing = 2.f;
	glm::vec3 ingredientOfTwoPos = glm::vec3(24.5f, 5.f, 18.f);
	float ingredientOfTwoSpacing = 2.5f;
	float ingredientXOffset = 8.25f;

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
		plate->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(plate);
		for (int o = 0; o < 3; ++o) {
			Onion* onion = new Onion();
			onion->init(program);
			onion->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * o - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
			recipeModels.push_back(onion);
		}
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::TOMATO_SOUP:
	{
		std::vector<Item*> recipeModels;
		Plate* plate = new Plate();
		plate->init(program);
		plate->addFood(new TomatoSoup());
		plate->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(plate);
		for (int t = 0; t < 3; ++t) {
			Tomato* tomato = new Tomato();
			tomato->init(program);
			tomato->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * t - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
			recipeModels.push_back(tomato);
		}
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::MUSHROOM_SOUP:
	{
		std::vector<Item*> recipeModels;
		Plate* plate = new Plate();
		plate->init(program);
		plate->addFood(new MushroomSoup());
		plate->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(plate);
		for (int m = 0; m < 3; ++m) {
			Mushroom* mushroom = new Mushroom();
			mushroom->init(program);
			mushroom->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * m - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
			recipeModels.push_back(mushroom);
		}
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::SALAD:
	{
		std::vector<Item*> recipeModels;
		Tomato* tomato = new Tomato();
		tomato->init(program);
		Lettuce* lettuce = new Lettuce();
		lettuce->init(program);
		Salad* salad = new Salad();
		salad->init(program);

		salad->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(salad);
		lettuce->setPosition(glm::vec3(ingredientOfTwoPos.x - pendingRecipes.size() * ingredientXOffset, ingredientOfTwoPos.y, ingredientOfTwoPos.z));
		recipeModels.push_back(lettuce);
		tomato->setPosition(glm::vec3(ingredientOfTwoPos.x - ingredientOfTwoSpacing - pendingRecipes.size() * ingredientXOffset, ingredientOfTwoPos.y, ingredientOfTwoPos.z));
		recipeModels.push_back(tomato);
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::BURGER:
	{
		std::vector<Item*> recipeModels;
		Bread* bread = new Bread();
		bread->init(program);
		Beef* beef = new Beef();
		beef->init(program);
		Burger* burger = new Burger();
		burger->init(program);
		burger->addIngredient(bread);
		Beef* cookedBeef = new Beef();
		cookedBeef->cut();
		cookedBeef->cook();
		burger->addIngredient(cookedBeef);

		burger->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(burger);
		bread->setPosition(glm::vec3(ingredientOfTwoPos.x - pendingRecipes.size() * ingredientXOffset, ingredientOfTwoPos.y, ingredientOfTwoPos.z));
		recipeModels.push_back(bread);
		beef->setPosition(glm::vec3(ingredientOfTwoPos.x - ingredientOfTwoSpacing - pendingRecipes.size() * ingredientXOffset, ingredientOfTwoPos.y, ingredientOfTwoPos.z));
		recipeModels.push_back(beef);
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::BURGER_CHEESE:
	{
		std::vector<Item*> recipeModels;
		Bread* bread = new Bread();
		bread->init(program);
		Beef* beef = new Beef();
		beef->init(program);
		Cheese* cheese = new Cheese();
		cheese->init(program);
		Burger* burger = new Burger();
		burger->init(program);
		burger->addIngredient(bread);
		Beef* cookedBeef = new Beef();
		cookedBeef->cut();
		cookedBeef->cook();
		burger->addIngredient(cookedBeef);
		Cheese* cutCheese = new Cheese();
		cutCheese->cut();
		burger->addIngredient(cutCheese);
		
		burger->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(burger);
		bread->setPosition(glm::vec3(ingredientOfThreePos.x - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(bread);
		beef->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(beef);
		cheese->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * 2.f - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(cheese);
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::BURGER_TOMATO:
	{
		std::vector<Item*> recipeModels;
		Bread* bread = new Bread();
		bread->init(program);
		Beef* beef = new Beef();
		beef->init(program);
		Tomato* tomato = new Tomato();
		tomato->init(program);
		Burger* burger = new Burger();
		burger->init(program);
		burger->addIngredient(bread);
		Beef* cookedBeef = new Beef();
		cookedBeef->cut();
		cookedBeef->cook();
		burger->addIngredient(cookedBeef);
		Tomato* cutTomato = new Tomato();
		cutTomato->cut();
		burger->addIngredient(cutTomato);

		burger->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(burger);
		bread->setPosition(glm::vec3(ingredientOfThreePos.x - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(bread);
		beef->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(beef);
		tomato->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * 2.f - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(tomato);
		pendingRecipes.push_back(recipeModels);
		break;
	}
	case Level::BURGER_LETTUCE:
	{
		std::vector<Item*> recipeModels;
		Bread* bread = new Bread();
		bread->init(program);
		Beef* beef = new Beef();
		beef->init(program);
		Lettuce* lettuce = new Lettuce();
		lettuce->init(program);
		Burger* burger = new Burger();
		burger->init(program);
		burger->addIngredient(bread);
		Beef* cookedBeef = new Beef();
		cookedBeef->cut();
		cookedBeef->cook();
		burger->addIngredient(cookedBeef);
		Lettuce* cutLettuce = new Lettuce();
		cutLettuce->cut();
		burger->addIngredient(cutLettuce);

		burger->setPosition(glm::vec3(recipePos.x - pendingRecipes.size() * recipeXOffset, recipePos.y, recipePos.z));
		recipeModels.push_back(burger);
		bread->setPosition(glm::vec3(ingredientOfThreePos.x - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(bread);
		beef->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(beef);
		lettuce->setPosition(glm::vec3(ingredientOfThreePos.x - ingredientOfThreeSpacing * 2.f - pendingRecipes.size() * ingredientXOffset, ingredientOfThreePos.y, ingredientOfThreePos.z));
		recipeModels.push_back(lettuce);
		pendingRecipes.push_back(recipeModels);
		break;
	}
	default:
		break;
	}
}






























