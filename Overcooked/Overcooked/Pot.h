#ifndef _POT_INCLUDE
#define _POT_INCLUDE

#include "Tool.h"

class Pot :
	public Tool
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void setPosition(const glm::vec3 pos);

	bool addFood(Food* food);

	bool hasFood();

private:
	bool foodIsValid(Food* food);

	void checkRecipe();

private:
	std::vector<Food*> foods;
};

#endif //_POT_INCLUDE