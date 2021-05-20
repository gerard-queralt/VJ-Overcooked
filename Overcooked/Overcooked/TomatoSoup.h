#ifndef _TOMATO_SOUP_INCLUDE
#define _TOMATO_SOUP_INCLUDE

#include "Food.h"

class TomatoSoup :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif // _TOMATO_SOUP_INCLUDE
