#include "FoodGenerator.h"

#include "Level.h"
#include "Beef.h"
#include "Tomato.h"

bool FoodGenerator::init(ShaderProgram & program)
{
	this->program = program;
	setScale(1.f);
	string path = "models/FoodPicker" + generates + ".obj";
	return loadFromFile(path, this->program);
}

void FoodGenerator::update(int deltaTime)
{
	if (this->item == NULL) {
		if (generates == "Beef") {
			item = new Beef();
		}
		else if (generates == "Tomato") {
			item = new Tomato();
		}
		if (this->item != NULL) {
			item->init(program);
			item->setPosition(position);
			item->setPlayer(player);
			level->addItem(item);
		}
	}
	Table::update(deltaTime);
}

void FoodGenerator::setFood(string food)
{
	generates = food;
}
