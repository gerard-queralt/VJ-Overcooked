#ifndef _FRYING_PAN_INCLUDE
#define _FRYING_PAN_INCLUDE

#include "Tool.h"

class FryingPan :
	public Tool
{
public:
	bool init(ShaderProgram &program);
};

#endif // _FRYING_PAN_INCLUDE