#ifndef _CHEESE_INCLUDE
#define _CHEESE_INCLUDE

#include "Food.h"

class Cheese :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif _CHEESE_INCLUDE