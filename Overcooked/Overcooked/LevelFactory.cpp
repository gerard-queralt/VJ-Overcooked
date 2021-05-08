#include "LevelFactory.h"
#include "FryingPan.h"
#include "Onion.h"

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
	Level *lvl = Level::createLevel(glm::vec3(32, 4, 32), texProgram, "images/floor.png", "images/wall.png");
	
	FryingPan* pan = new FryingPan();
	pan->init(texProgram);
	pan->setPosition(glm::vec3(5.f, 0.f, 0.f));
	pan->setScale(2.f);
	lvl->addItem(pan);

	Onion* onion = new Onion();
	onion->init(texProgram);
	onion->setPosition(glm::vec3(0.f, 0.f, 0.f));
	onion->setScale(4.f);
	lvl->addItem(onion);

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
