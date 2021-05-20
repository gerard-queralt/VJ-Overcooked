#ifndef _MUSHROOM_INCLUDE
#define _MUSHROOM_INCLUDE

#include "Food.h"

class Mushroom :
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

#endif //_MUSHROOM_INCLUDE

