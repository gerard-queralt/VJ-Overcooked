#ifndef _TRASH_CAN_INCLUDE
#define _TRASH_CAN_INCLUDE

#include "Table.h"

class TrashCan :
	public Table
{
public:
	bool init(ShaderProgram &program);
	virtual void render(ShaderProgram & program, glm::mat4 viewMatrix);
	bool setItem(Item* item);


private:
	bool facingUpdated = false;
	bool notFacingUpdated = false;
};

#endif //_TRASH_CAN_INCLUDE