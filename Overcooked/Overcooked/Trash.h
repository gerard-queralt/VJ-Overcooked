#ifndef _TRASH_INCLUDE
#define _TRASH_INCLUDE

#include "Food.h"

class Trash :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif //_TRASH_INCLUDE