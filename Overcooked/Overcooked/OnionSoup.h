#ifndef _ONION_SOUP_INCLUDE
#define _ONION_SOUP_INCLUDE

#include "Food.h"

class OnionSoup :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif // _ONION_SOUP_INCLUDE