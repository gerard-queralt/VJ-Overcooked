#ifndef _SALAD_INCLUDE
#define _SALAD_INCLUDE

#include "Food.h"

class Salad :
	public Food
{
public:
	bool init(ShaderProgram &program);

	string whatAmI();
};

#endif //_SALAD_INCLUDE