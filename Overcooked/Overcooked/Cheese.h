#ifndef _CHEESE_INCLUDE
#define _CHEESE_INCLUDE

#include "Food.h"

class Cheese :
	public Food
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void cut();
	bool isCut();

	string whatAmI();

private:
	bool cutBool = false;
	bool updated = true;
};

#endif _CHEESE_INCLUDE