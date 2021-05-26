#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "AssimpModel.h"

class Level; //forward declaration
class Player; //forward declaration

class Entity
{
public:
	virtual bool init(ShaderProgram &program) = 0;
	virtual void update(int deltaTime);
	virtual void render(ShaderProgram & program, glm::mat4 viewMatrix);

	float getHeight() const;
	glm::vec3 getCenter() const;

	virtual void setPosition(const glm::vec3 pos);
	glm::vec3 getPosition() const;

	void setScale(const float scale);
	float getScale() const;

	void setRotation(const float rotation);
	float getRotation() const;

	std::vector<glm::vec3> getBoundingBox();

	void setPlayer(Player *player);
	void setLevel(Level *level);

protected:
	bool loadFromFile(const string &filename, ShaderProgram &program);

	bool inContactWithPlayer();

protected:
	AssimpModel *model;
	glm::vec3 position;
	float scale;
	float rotation;

	Player *player;
	Level *level;
};

#endif // _ENTITY_INCLUDE