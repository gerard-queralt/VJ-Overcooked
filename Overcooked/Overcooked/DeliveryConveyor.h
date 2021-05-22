#ifndef _DELIVERY_CONVEYOR_INCLUDE
#define _DELIVERY_CONVEYOR_INCLUDE

#include "Table.h"

class DeliveryConveyor :
	public Table
{
public:
	bool init(ShaderProgram &program);

	bool setItem(Item* item);
};

#endif //_DELIVERY_CONVEYOR_INCLUDE