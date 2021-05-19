#ifndef _BREAD_INCLUDE
#define _BREAD_INCLUDE

#include "Food.h"

class Bread :
	public Food
{
public:
	bool init(ShaderProgram &program);
	
	string whatAmI();
};

#endif // _BREAD_INCLUDE