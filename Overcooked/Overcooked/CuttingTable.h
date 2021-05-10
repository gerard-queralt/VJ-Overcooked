#ifndef _CUTTING_TABLE_INCLUDE
#define _CUTTING_TABLE_INCLUDE

#include "Table.h"
#include "Billboard.h"

class CuttingTable :
	public Table
{
public:
	bool init(ShaderProgram &program);
	void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

private:
	Billboard* working;

	int cuttingTime = 0;
};

#endif //_CUTTING_TABLE_INCLUDE