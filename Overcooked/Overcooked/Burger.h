#ifndef _BURGER_INCLUDE
#define _BURGER_INCLUDE

#include "Food.h"

class Burger :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();

private:
	ShaderProgram program;
};

#endif //_BURGER_INCLUDE