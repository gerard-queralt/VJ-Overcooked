#include "CuttingTable.h"

#include "Player.h"

bool CuttingTable::init(ShaderProgram & program)
{
	setScale(1.f);
	return loadFromFile("models/CuttingTable.obj", program);
}

void CuttingTable::update(int deltaTime)
{
	
}
