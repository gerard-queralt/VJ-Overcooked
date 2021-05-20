#ifndef _TOMATO_INCLUDE
#define _TOMATO_INCLUDE

#include "Food.h"

class Tomato :
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

#endif //_TOMATO_INCLUDE

