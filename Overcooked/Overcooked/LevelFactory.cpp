#include "LevelFactory.h"
#include "FryingPan.h"
#include "Pot.h"
#include "Plate.h"
#include "Onion.h"
#include "Tomato.h"
#include "Mushroom.h"
#include "Beef.h"
#include "CuttingTable.h"
#include "Stove.h"
#include "FoodGenerator.h"
#include "Bread.h"
#include "TrashCan.h"
#include "Cheese.h"
#include "Lettuce.h"
#include "DeliveryConveyor.h"
#include "Extinguisher.h"

Level* LevelFactory::createLevel(int level, ShaderProgram texProgram)
{
	switch (level)
	{
	case 1:
		return createLevel1(texProgram);
	case 2:
		return createLevel2(texProgram);
	case 3:
		return createLevel3(texProgram);
	case 4:
		return createLevel4(texProgram);
	case 5:
		return createLevel5(texProgram);
	default:
		return NULL;
	}
}

Level* LevelFactory::createLevel1(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(1, 0);
	lvl->setPoints(150);
	lvl->addPossibleRecipe(Level::BURGER);
	lvl->addPossibleRecipe(Level::SALAD);
	
	FryingPan* pan = new FryingPan();
	pan->init(texProgram);
	pan->setPosition(glm::vec3(5.f, 0.f, 0.f));
	lvl->addItem(pan);

	Table* t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(6.f, 0.f, 14.f));
	lvl->addTable(t);

	CuttingTable* ct = new CuttingTable();
	ct->init(texProgram);
	ct->setPosition(glm::vec3(2.f, 0.f, 14.f));
	lvl->addTable(ct);

	Plate* plate = new Plate();
	plate->init(texProgram);
	t->setItem(plate);
	lvl->addItem(plate);
	plate->setLevel(lvl);

	Pot* pot = new Pot();
	pot->init(texProgram);
	pot->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	lvl->addItem(pot);

	Stove* stove = new Stove();
	stove->init(texProgram);
	stove->setPosition(glm::vec3(-2.f, 0.f, 14.f));
	lvl->addTable(stove);

	TrashCan* tc = new TrashCan();
	tc->init(texProgram);
	tc->setPosition(glm::vec3(-6.f, 0.f, 14.f));
	lvl->addTable(tc);

	DeliveryConveyor* dc = new DeliveryConveyor();
	dc->init(texProgram);
	dc->setRotation(90.f);
	dc->setPosition(glm::vec3(-14.f, 0.f, 8.f));
	dc->setLevel(lvl);
	lvl->addTable(dc);

	Extinguisher* e = new Extinguisher();
	e->init(texProgram);
	e->setPosition(glm::vec3(-12.f, 0.f, 0.f));
	e->setLevel(lvl);
	lvl->addItem(e);

	FoodGenerator* fg = new FoodGenerator();
	fg->setFood("Onion");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, 10.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Mushroom");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, 6.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Tomato");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, 2.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Lettuce");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -2.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Bread");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -6.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Beef");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -10.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Cheese");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -14.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	return lvl;
}

Level* LevelFactory::createLevel2(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(2, 30);
	lvl->setPoints(450);
	lvl->addPossibleRecipe(Level::ONION_SOUP);
	lvl->addPossibleRecipe(Level::TOMATO_SOUP);
	lvl->addPossibleRecipe(Level::MUSHROOM_SOUP);

	Table* t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, 14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(10.f, 0.f, 14.f));
	lvl->addTable(t);

	Extinguisher* e = new Extinguisher();
	e->init(texProgram);
	e->setLevel(lvl);
	lvl->addItem(e);
	t->setItem(e);
	e->setRotation(90.f);

	Stove* stove = new Stove();
	stove->init(texProgram);
	stove->setPosition(glm::vec3(6.f, 0.f, 14.f));
	lvl->addTable(stove);

	Pot* pot = new Pot();
	pot->init(texProgram);
	lvl->addItem(pot);
	stove->setItem(pot);

	stove = new Stove();
	stove->init(texProgram);
	stove->setPosition(glm::vec3(2.f, 0.f, 14.f));
	lvl->addTable(stove);

	pot = new Pot();
	pot->init(texProgram);
	lvl->addItem(pot);
	stove->setItem(pot);
	
	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-2.f, 0.f, 14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-6.f, 0.f, 14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-10.f, 0.f, 14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-14.f, 0.f, 14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, 10.f));
	lvl->addTable(t);

	FoodGenerator* fg = new FoodGenerator();
	fg->setFood("Onion");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, 6.f));
	fg->setRotation(270.f);
	fg->setLevel(lvl);
	lvl->addTable(fg);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, 2.f));
	lvl->addTable(t);

	fg = new FoodGenerator();
	fg->setFood("Mushroom");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -2.f));
	fg->setRotation(270.f);
	fg->setLevel(lvl);
	lvl->addTable(fg);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, -6.f));
	lvl->addTable(t);

	fg = new FoodGenerator();
	fg->setFood("Tomato");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(14.f, 0.f, -10.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-14.f, 0.f, 10.f));
	lvl->addTable(t);

	DeliveryConveyor* dc = new DeliveryConveyor();
	dc->init(texProgram);
	dc->setRotation(90.f);
	dc->setPosition(glm::vec3(-14.f, 0.f, 4.f));
	dc->setLevel(lvl);
	lvl->addTable(dc);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-14.f, 0.f, -2.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-14.f, 0.f, -6.f));
	lvl->addTable(t);

	TrashCan* tc = new TrashCan();
	tc->init(texProgram);
	tc->setPosition(glm::vec3(-14.f, 0.f, -10.f));
	lvl->addTable(tc);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-14.f, 0.f, -14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-10.f, 0.f, -14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-6.f, 0.f, -14.f));
	lvl->addTable(t);

	Plate* plate = new Plate();
	plate->init(texProgram);
	lvl->addItem(plate);
	plate->setLevel(lvl);
	t->setItem(plate);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-2.f, 0.f, -14.f));
	lvl->addTable(t);

	plate = new Plate();
	plate->init(texProgram);
	lvl->addItem(plate);
	plate->setLevel(lvl);
	t->setItem(plate);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(2.f, 0.f, -14.f));
	lvl->addTable(t);

	plate = new Plate();
	plate->init(texProgram);
	lvl->addItem(plate);
	plate->setLevel(lvl);
	t->setItem(plate);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(6.f, 0.f, -14.f));
	lvl->addTable(t);

	plate = new Plate();
	plate->init(texProgram);
	lvl->addItem(plate);
	plate->setLevel(lvl);
	t->setItem(plate);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(10.f, 0.f, -14.f));
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, -14.f));
	lvl->addTable(t);

	CuttingTable* ct = new CuttingTable();
	ct->init(texProgram);
	ct->setPosition(glm::vec3(-2.f, 0.f, -2.f));
	lvl->addTable(ct);

	ct = new CuttingTable();
	ct->init(texProgram);
	ct->setPosition(glm::vec3(2.f, 0.f, 2.f));
	ct->setRotation(180.f);
	lvl->addTable(ct);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(-2.f, 0.f, 2.f));
	t->setRotation(180.f);
	lvl->addTable(t);

	t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(2.f, 0.f, -2.f));
	lvl->addTable(t);

	return lvl;
}

Level* LevelFactory::createLevel3(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(1, 30);
	lvl->setPoints(150);
	lvl->addPossibleRecipe(Level::ONION_SOUP);
	return lvl;
}

Level* LevelFactory::createLevel4(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(1, 30);
	lvl->setPoints(150);
	lvl->addPossibleRecipe(Level::ONION_SOUP);
	return lvl;
}

Level* LevelFactory::createLevel5(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(1, 30);
	lvl->setPoints(150);
	lvl->addPossibleRecipe(Level::ONION_SOUP);
	lvl->addPossibleRecipe(Level::TOMATO_SOUP);
	lvl->addPossibleRecipe(Level::MUSHROOM_SOUP);
	lvl->addPossibleRecipe(Level::BURGER_CHEESE);
	lvl->addPossibleRecipe(Level::BURGER_TOMATO);
	lvl->addPossibleRecipe(Level::BURGER_LETTUCE);
	lvl->addPossibleRecipe(Level::BURGER);
	lvl->addPossibleRecipe(Level::SALAD);
	return lvl;
}
