#ifndef _CUTTING_TABLE_INCLUDE
#define _CUTTING_TABLE_INCLUDE

#include "Entity.h"

class CuttingTable :
	public Entity
{
public:
	bool init(ShaderProgram &program);
};

#endif //_CUTTING_TABLE_INCLUDE