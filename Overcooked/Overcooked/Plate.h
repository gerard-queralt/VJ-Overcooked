#ifndef _PLATE_INCLUDE
#define _PLATE_INCLUDE

#include "Tool.h"

class Plate :
	public Tool
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void setPosition(const glm::vec3 pos);

	bool addFood(Food* food);

	bool hasFood();

	Food* getFood();
	void empty();

	string whatAmI();

private:
	bool assembleRecipe(Food* addedFood);

	bool partOfBurgerRecipe(Food* food);

private:
	ShaderProgram program;

	Food* food;

	bool onionSoup = false;
	bool tomatoSoup = false;
	bool mushroomSoup = false;
	bool trash = false;
};

#endif //_PLATE_INCLUDE