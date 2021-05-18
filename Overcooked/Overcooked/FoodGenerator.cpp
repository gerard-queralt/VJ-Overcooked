#include "FoodGenerator.h"

bool FoodGenerator::init(ShaderProgram & program)
{
	setScale(1.f);
	string path = "models/FoodPicker" + generates + ".obj";
	return loadFromFile(path, program);
}

void FoodGenerator::setFood(string food)
{
	generates = food;
}
