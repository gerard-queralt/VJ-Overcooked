#ifndef _EXTINGUISHER_INCLUDE
#define _EXTINGUISHER_INCLUDE

#include "Tool.h"

class Extinguisher :
	public Tool
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	void use();
	void stop();

	string whatAmI();

private:
	bool inUse;
};

#endif // _EXTINGUISHER_INCLUDE