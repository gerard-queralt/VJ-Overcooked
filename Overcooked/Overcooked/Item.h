#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Entity.h"

class Item :
	public Entity
{
public:
	void update(int deltaTime);

	virtual bool isFood() = 0;

	virtual string whatAmI() = 0;

	virtual Item* clone(); //aquest metode només l'utilitzarem per a les receptes en la funcio Level::getNextPendingRecipe, per aixo per defecte torna NULL i nomes esta implementat en les classes Burger, Salad i Plate
};

#endif // _ITEM_INCLUDE