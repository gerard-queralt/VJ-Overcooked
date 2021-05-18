#ifndef _BEEF_INCLUDE
#define _BEEF_INCLUDE

#include "Food.h"

class Beef :
	public Food
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void cut();
	bool isCut();

	void cook();
	bool isCooked();

	string whatAmI();

private:
	bool cutBool = false;
	bool cutUpdated = true;
	bool cookedBool = false;
	bool cookedUpdated = true;
};

#endif //_BEEF_INCLUDE