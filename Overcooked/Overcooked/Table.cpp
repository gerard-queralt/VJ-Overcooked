#include "Table.h"

bool Table::init(ShaderProgram & program)
{
	return loadFromFile("models/EmptyTable.obj", program);
}

void Table::setItem(Item * item)
{
	this->item = item;
}
