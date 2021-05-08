#include "CuttingTable.h"

#include "Player.h"

bool CuttingTable::init(ShaderProgram & program)
{
	return loadFromFile("models/CuttingTable.obj", program);
}

void CuttingTable::update(int deltaTime)
{
	
}
