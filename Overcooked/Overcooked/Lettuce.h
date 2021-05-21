#ifndef _LETTUCE_INCLUDE
#define _LETTUCE_INCLUDE

#include "Food.h"

class Lettuce :
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

#endif //_LETUCE_INCLUDE