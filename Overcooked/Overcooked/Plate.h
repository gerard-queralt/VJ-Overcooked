#ifndef _PLATE_INCLUDE
#define _PLATE_INCLUDE

#include "Tool.h"

class Plate :
	public Tool
{
public:
	bool init(ShaderProgram &program);

	void setPosition(const glm::vec3 pos);

	bool addFood(Food* food);

	bool hasFood();

private:
	Food* food;
};

#endif //_PLATE_INCLUDE