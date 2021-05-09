#ifndef _ONION_INCLUDE
#define _ONION_INCLUDE

#include "Food.h"

class Onion :
	public Food
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void cut();
	bool isCut();

private:
	bool cutBool = false;
	bool updated = true;
};

#endif //_ONION_INCLUDE