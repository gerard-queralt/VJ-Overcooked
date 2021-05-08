#ifndef _ONION_INCLUDE
#define _ONION_INCLUDE

#include "Food.h"

class Onion :
	public Food
{
public:
	bool init(ShaderProgram &program);
};

#endif //_ONION_INCLUDE