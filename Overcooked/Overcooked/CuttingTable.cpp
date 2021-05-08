#include "CuttingTable.h"

bool CuttingTable::init(ShaderProgram & program)
{
	return loadFromFile("table_tmp/chr_swordless.obj", program);
}
