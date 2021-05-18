#include "LevelFactory.h"
#include "FryingPan.h"
#include "Pot.h"
#include "Plate.h"
#include "Onion.h"
#include "Beef.h"
#include "CuttingTable.h"
#include "Stove.h"
#include "FoodGenerator.h"

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
	
	FryingPan* pan = new FryingPan();
	pan->init(texProgram);
	pan->setPosition(glm::vec3(5.f, 0.f, 0.f));
	lvl->addItem(pan);

	Onion* onion = new Onion();
	onion->init(texProgram);
	onion->setPosition(glm::vec3(0.f, 0.f, 0.f));
	lvl->addItem(onion);

	onion = new Onion();
	onion->init(texProgram);
	onion->setPosition(glm::vec3(10.f, 0.f, 0.f));
	lvl->addItem(onion);

	Table* t = new Table();
	t->init(texProgram);
	t->setPosition(glm::vec3(14.f, 0.f, 14.f));
	lvl->addTable(t);

	CuttingTable* ct = new CuttingTable();
	ct->init(texProgram);
	ct->setPosition(glm::vec3(10.f, 0.f, 14.f));
	lvl->addTable(ct);

	//Ceba que posem a la taula de tallar
	Onion* onion2 = new Onion();
	onion2->init(texProgram);
	ct->setItem(onion2);
	lvl->addItem(onion2);

	//Plat que posem a la taula buida
	Plate* plate = new Plate();
	plate->init(texProgram);
	t->setItem(plate);
	lvl->addItem(plate);

	Pot* pot = new Pot();
	pot->init(texProgram);
	pot->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	pot->setLevel(lvl);
	lvl->addItem(pot);

	Stove* stove = new Stove();
	stove->init(texProgram);
	stove->setPosition(glm::vec3(6.f, 0.f, 14.f));
	lvl->addTable(stove);

	FoodGenerator* fg = new FoodGenerator();
	fg->setFood(new Beef());
	fg->init(texProgram);
	fg->setPosition(glm::vec3(2.f, 0.f, 14.f));
	lvl->addTable(fg);

	return lvl;
}

Level* LevelFactory::createLevel2(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor.png", "images/wall.png");
	return lvl;
}

Level* LevelFactory::createLevel3(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor.png", "images/wall.png");
	return lvl;
}

Level* LevelFactory::createLevel4(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor.png", "images/wall.png");
	return lvl;
}

Level* LevelFactory::createLevel5(ShaderProgram texProgram)
{
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor.png", "images/wall.png");
	return lvl;
}
