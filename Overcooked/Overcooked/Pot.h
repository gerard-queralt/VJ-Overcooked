#ifndef _POT_INCLUDE
#define _POT_INCLUDE

#include "Tool.h"

class Pot :
	public Tool
{
public:
	bool init(ShaderProgram &program);

	void setPosition(const glm::vec3 pos);

	bool addFood(Food* food);

private:
	std::vector<Food*> foods;
};

#endif //_POT_INCLUDE