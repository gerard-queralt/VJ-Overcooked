#ifndef _TABLE_INCLUDE
#define _TABLE_INCLUDE

#include "Entity.h"
#include "Item.h"

class Table :
	public Entity
{
public:
	virtual bool init(ShaderProgram &program);
	virtual void render(ShaderProgram & program, glm::mat4 viewMatrix);
	void update(int deltaTime);

	virtual bool setItem(Item* item);

	bool collisionWithPlayer();

	bool playerFacingThis();

protected:
	Item* item = NULL;

private:
	bool facingUpdated = false;
	bool notFacingUpdated = false;
};

#endif //_TABLE_INCLUDE