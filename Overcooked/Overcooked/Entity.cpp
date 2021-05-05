#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Player.h"

bool Entity::loadFromFile(const string & filename, ShaderProgram & program)
{
	model = new AssimpModel();
	return model->loadFromFile(filename, program);
}

void Entity::update(int deltaTime)
{
}

void Entity::render(ShaderProgram & program, glm::mat4 viewMatrix) const
{
	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;
	glm::vec3 centerModelBase = getCenter() - glm::vec3(0.f, getHeight() / 2.f, 0.f);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, -2.f, 0.f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
	modelMatrix = glm::translate(modelMatrix, -centerModelBase);
	program.setUniformMatrix4f("modelview", viewMatrix * modelMatrix);

	normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
	program.setUniformMatrix3f("normalmatrix", normalMatrix);
	
	model->render(program);
}

float Entity::getHeight() const
{
	return model->getHeight();
}

glm::vec3 Entity::getCenter() const
{
	return model->getCenter();
}

void Entity::setPosition(const glm::vec3 pos)
{
	this->position = pos;
}

glm::vec3 Entity::getPosition() const
{
	return position;
}

void Entity::setScale(const float scale)
{
	this->scale = scale;
}

float Entity::getScale() const
{
	return scale;
}

std::vector<glm::vec3> Entity::getBoundingBox()
{
	std::vector<glm::vec3> bbox = model->getBoundingBox();
	
	//la desplacem a la posicio de l'entitat
	bbox[0] += position;
	bbox[1] += position;
	
	//l'escalem
	bbox[0] *= scale/model->getHeight();
	bbox[1] *= scale / model->getHeight();

	return bbox;
}

void Entity::setPlayer(Player * player)
{
	this->player = player;
}

void Entity::setLevel(Level *level)
{
	this->level = level;
}

bool Entity::inContactWithPlayer()
{
	std::vector<glm::vec3> bbox = getBoundingBox();
	std::vector<glm::vec3> playerBbox = player->getBoundingBox();
	return glm::all(glm::lessThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::greaterThanEqual(bbox[1], playerBbox[1]));
}
