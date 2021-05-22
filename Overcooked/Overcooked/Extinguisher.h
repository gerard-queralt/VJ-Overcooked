#ifndef _EXTINGUISHER_INCLUDE
#define _EXTINGUISHER_INCLUDE

#include "Tool.h"

class Extinguisher :
	public Tool
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif // _EXTINGUISHER_INCLUDE