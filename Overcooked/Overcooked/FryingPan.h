#ifndef _FRYING_PAN_INCLUDE
#define _FRYING_PAN_INCLUDE

#include "Tool.h"

class FryingPan :
	public Tool
{
public:
	bool init(ShaderProgram &program);
	void update(int deltaTime);

	void setPosition(const glm::vec3 pos);

	bool addFood(Food* food);

	bool hasFood();

	bool finished();
	Food* getFood();
	void empty();

	string whatAmI();

private:
	bool foodIsValid(Food* food);

private:
	Food* food;
};

#endif // _FRYING_PAN_INCLUDE