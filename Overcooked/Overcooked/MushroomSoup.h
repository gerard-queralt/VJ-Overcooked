#ifndef _MUSHROOM_SOUP_INCLUDE
#define _MUSHROOM_SOUP_INCLUDE

#include "Food.h"

class MushroomSoup :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif // _MUSHROOM_SOUP_INCLUDE

