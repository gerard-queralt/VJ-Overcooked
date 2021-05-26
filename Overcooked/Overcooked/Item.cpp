#include "Item.h"
#include "Player.h"

void Item::update(int deltaTime)
{
	if (inContactWithPlayer()) {
		player->hold(this);
	}
}

Item * Item::clone()
{
	return NULL;
}
