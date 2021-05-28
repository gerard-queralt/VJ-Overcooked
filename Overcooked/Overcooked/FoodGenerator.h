#ifndef _FOOD_GENERATOR_INCLUDE
#define _FOOD_GENERATOR_INCLUDE

#include "Table.h"
#include "Food.h"

class FoodGenerator :
	public Table
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

	void setFood(string food);

private:
	ShaderProgram program;

	string generates;

	bool facingUpdated = false;
	bool notFacingUpdated = false;

	bool firstGenerate = true;
};

#endif //_FOOD_GENERATOR_INCLUDE