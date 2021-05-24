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
	lvl->setTime(1, 30);
	lvl->setPoints(150);
	//lvl->addPossibleRecipe(Level::ONION_SOUP);
	lvl->addPossibleRecipe(Level::TOMATO_SOUP);
	lvl->addPossibleRecipe(Level::MUSHROOM_SOUP);
	//lvl->addPossibleRecipe(Level::BURGER_CHEESE);
	//lvl->addPossibleRecipe(Level::BURGER_TOMATO);
	//lvl->addPossibleRecipe(Level::BURGER_LETTUCE);
	//lvl->addPossibleRecipe(Level::BURGER);
	//lvl->addPossibleRecipe(Level::SALAD);
	
	FryingPan* pan = new FryingPan();
	pan->init(texProgram);
	pan->setPosition(glm::vec3(5.f, 0.f, 0.f));
	lvl->addItem(pan);

	Mushroom* mushroom = new Mushroom();
	mushroom->init(texProgram);
	mushroom->setPosition(glm::vec3(0.f, 0.f, 0.f));
	lvl->addItem(mushroom);

	mushroom = new Mushroom();
	mushroom->init(texProgram);
	mushroom->setPosition(glm::vec3(10.f, 0.f, 0.f));
	lvl->addItem(mushroom);

	Table* t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, 14.f));
	lvl->addTable(t);

	CuttingTable* ct = new CuttingTable();
	ct->init(texProgram);
	ct->setPosition(glm::vec3(10.f, 0.f, 14.f));
	lvl->addTable(ct);

	//Ceba que posem a la taula de tallar
	Mushroom* mushroom2 = new Mushroom();
	mushroom2->init(texProgram);
	ct->setItem(mushroom2);
	lvl->addItem(mushroom2);

	//Plat que posem a la taula buida
	Plate* plate = new Plate();
	plate->init(texProgram);
	t->setItem(plate);
	lvl->addItem(plate);
	plate->setLevel(lvl);

	Pot* pot = new Pot();
	pot->init(texProgram);
	pot->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	//pot->setLevel(lvl);
	lvl->addItem(pot);

	Stove* stove = new Stove();
	stove->init(texProgram);
	stove->setPosition(glm::vec3(6.f, 0.f, 14.f));
	lvl->addTable(stove);

	FoodGenerator* fg = new FoodGenerator();
	fg->setFood("Beef");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(2.f, 0.f, 14.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	fg = new FoodGenerator();
	fg->setFood("Tomato");
	fg->init(texProgram);
	fg->setPosition(glm::vec3(-2.f, 0.f, 14.f));
	fg->setLevel(lvl);
	lvl->addTable(fg);

	Bread* bread = new Bread();
	bread->init(texProgram);
	bread->setPosition(glm::vec3(-5.f, 0.f, 5.f));
	lvl->addItem(bread);

	TrashCan* tc = new TrashCan();
	tc->init(texProgram);
	tc->setPosition(glm::vec3(-6.f, 0.f, 14.f));
	lvl->addTable(tc);

	Cheese* c = new Cheese();
	c->init(texProgram);
	c->setPosition(glm::vec3(-15.f, 0.f, -15.f));
	lvl->addItem(c);

	Lettuce* l = new Lettuce();
	l->init(texProgram);
	l->setPosition(glm::vec3(-10.f, 0.f, -10.f));
	lvl->addItem(l);

	DeliveryConveyor* dc = new DeliveryConveyor();
	dc->init(texProgram);
	dc->setRotation(90.f);
	dc->setPosition(glm::vec3(-14.f, 0.f, 8.f));
	dc->setLevel(lvl);
	lvl->addTable(dc);

	return lvl;
}

Level* LevelFactory::createLevel2(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor1.png", "images/wall1.png");
	lvl->setTime(1, 30);
	lvl->setPoints(150);
	lvl->addPossibleRecipe(Level::ONION_SOUP);
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
	return lvl;
}
