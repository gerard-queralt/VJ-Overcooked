#include "FoodGenerator.h"

#include "Level.h"

#include "Bread.h"
#include "Beef.h"
#include "Tomato.h"
#include "Mushroom.h"
#include "Onion.h"
#include "Cheese.h"
#include "Lettuce.h"

#include "Music.h"

bool FoodGenerator::init(ShaderProgram & program)
{
	this->program = program;
	setScale(1.f);
	string path = "models/FoodPicker" + generates + ".obj";
	return loadFromFile(path, this->program);
}

void FoodGenerator::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	if (playerFacingThis() && !facingUpdated) {
		loadFromFile("models/FoodPicker" + generates + "Soft.obj", program);
		facingUpdated = true;
		notFacingUpdated = false;
	}
	else if(!playerFacingThis() && !notFacingUpdated){
		loadFromFile("models/FoodPicker" + generates + ".obj", program);
		notFacingUpdated = true;
		facingUpdated = false;
	}
	Entity::render(program, viewMatrix);
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
		else if (generates == "Bread") {
			item = new Bread();
		}
		else if (generates == "Mushroom") {
			item = new Mushroom();
		}
		else if (generates == "Onion") {
			item = new Onion();
		}
		else if (generates == "Lettuce") {
			item = new Lettuce();
		}
		else if (generates == "Cheese") {
			item = new Cheese();
		}
		if (this->item != NULL) {
			item->init(program);
			item->setPosition(position);
			item->setPlayer(player);
			level->addItem(item);

			if (!firstGenerate) {
				Music::instance().playSoundEffect(6);
			}
			firstGenerate = false;
		}
	}
	Table::update(deltaTime);
}

void FoodGenerator::setFood(string food)
{
	generates = food;
}
