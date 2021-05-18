#include "FoodGenerator.h"

bool FoodGenerator::init(ShaderProgram & program)
{
	setScale(1.f);
	string path = "models/FoodPicker" + generates->whatAmI() + ".obj";
	return loadFromFile(path, program);
}

void FoodGenerator::setFood(Food * food)
{
	this->generates = food;
}
