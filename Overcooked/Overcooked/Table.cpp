#include "Table.h"

bool Table::init(ShaderProgram & program)
{
	return loadFromFile("models/EmptyTable.obj", program);
}

void Table::setItem(Item * item)
{
	item->setPosition(glm::vec3(position.x, 1.2f, position.z));
	this->item = item;
}
