#ifndef _DELIVERY_CONVEYOR_INCLUDE
#define _DELIVERY_CONVEYOR_INCLUDE

#include "Table.h"

class DeliveryConveyor :
	public Table
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);

	bool setItem(Item* item);

private:
	bool facingUpdated = false;
	bool notFacingUpdated = false;
};

#endif //_DELIVERY_CONVEYOR_INCLUDE