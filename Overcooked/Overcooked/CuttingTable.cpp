#include "CuttingTable.h"

bool CuttingTable::init(ShaderProgram & program)
{
	return loadFromFile("models/CuttingTable.obj", program);
}
