#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Level.h"

#define PI 3.14159f

bool Entity::loadFromFile(const string & filename, ShaderProgram & program)
{
	model = new AssimpModel();
	return model->loadFromFile(filename, program);
}

void Entity::update(int deltaTime)
{
}

void Entity::render(ShaderProgram & program, glm::mat4 viewMatrix)
{
	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;
	glm::vec3 centerModelBase = getCenter() - glm::vec3(0.f, getHeight() / 2.f, 0.f);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation * PI / 180, glm::vec3(0.f, 1.f, 0.f));
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

void Entity::setRotation(const float rotation)
{
	this->rotation = rotation;
	if (this->rotation >= 360)
		this->rotation -= 360;
	else if (this->rotation < 0)
		this->rotation += 360;
}

float Entity::getRotation() const
{
	return rotation;
}

std::vector<glm::vec3> Entity::getBoundingBox()
{
	std::vector<glm::vec3> bbox = model->getBoundingBox();
		
	//l'escalem
	bbox[0] *= scale; // model->getHeight();
	bbox[1] *= scale; // model->getHeight();

	//la desplacem a la posicio de l'entitat
	bbox[0] += position;
	bbox[1] += position;

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

	//ignorem la y
	bbox[0].y = 0;
	bbox[1].y = 0;
	playerBbox[0].y = 0;
	playerBbox[1].y = 0;

	bool en0InsidePlayer = glm::all(glm::greaterThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[0], playerBbox[1]));
	bool en1InsidePlayer = glm::all(glm::greaterThanEqual(bbox[1], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[1], playerBbox[1]));
	bool p0InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[0], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[0], bbox[1]));
	bool p1InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[1], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[1], bbox[1]));
	return en0InsidePlayer || en1InsidePlayer || p0InsideEntity || p1InsideEntity;
}
