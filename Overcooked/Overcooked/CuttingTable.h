#ifndef _CUTTING_TABLE_INCLUDE
#define _CUTTING_TABLE_INCLUDE

#include "Table.h"

class CuttingTable :
	public Table
{
public:
	bool init(ShaderProgram &program);

	void update(int deltaTime);
};

#endif //_CUTTING_TABLE_INCLUDE