#ifndef _TRASH_CAN_INCLUDE
#define _TRASH_CAN_INCLUDE

#include "Table.h"

class TrashCan :
	public Table
{
public:
	bool init(ShaderProgram &program);

	bool setItem(Item* item);

};

#endif //_TRASH_CAN_INCLUDE