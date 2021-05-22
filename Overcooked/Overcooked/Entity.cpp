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

	//la rotem
	/* DE MOMENT COMENTAT PERQUE BLOQUEJA EL MOVIMENT QUAN TOQUEM UNA PARET
	bbox[0].x = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
	bbox[0].z = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
	bbox[1].x = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
	bbox[1].z = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);
	*/

	//la desplacem a la posicio de l'entitat
	bbox[0] += position;
	bbox[1] += position;

	//ignorem la y
	bbox[0].y = 0;
	bbox[1].y = 0;

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

	//rotem la bbox de l'entitat

		//rotem respecte el 0,0
		bbox[0] -= position;
		bbox[1] -= position;

		float xPrime = bbox[0].x * cos(rotation * PI / 180) - bbox[0].z * sin(rotation * PI / 180);
		float zPrime = bbox[0].z * cos(rotation * PI / 180) + bbox[0].x * sin(rotation * PI / 180);
		bbox[0].x = xPrime;
		bbox[0].z = zPrime;
		xPrime = bbox[1].x * cos(rotation * PI / 180) - bbox[1].z * sin(rotation * PI / 180);
		zPrime = bbox[1].z * cos(rotation * PI / 180) + bbox[1].x * sin(rotation * PI / 180);
		bbox[1].x = xPrime;
		bbox[1].z = zPrime;

		//tornem a la posicio
		bbox[0] += position;
		bbox[1] += position;

		glm::vec3 eTopRight = glm::vec3(bbox[0].x, 0.f, bbox[1].z);
		glm::vec3 eBotLeft = glm::vec3(bbox[1].x, 0.f, bbox[0].z);

		glm::vec3 pTopRight = glm::vec3(playerBbox[0].x, 0.f, playerBbox[1].z);
		glm::vec3 pBotLeft = glm::vec3(playerBbox[1].x, 0.f, playerBbox[0].z);

		//ignorem la y
		bbox[0].y = 0;
		bbox[1].y = 0;
		playerBbox[0].y = 0;
		playerBbox[1].y = 0;

		//reajustem quin punt es quin, de manera que bbox[0] es sempre el punt de baix a la dreta
		if (rotation >= 45.f && rotation < 135.f) {
			glm::vec3 bbox0aux = bbox[0];
			glm::vec3 bbox1aux = bbox[1];
			bbox[0] = eBotLeft;
			bbox[1] = eTopRight;
			eBotLeft = bbox0aux;
			eTopRight = bbox1aux;
		}
		else if (rotation >= 135.f && rotation < 225.f) {
			glm::vec3 bbox0aux = bbox[0];
			glm::vec3 BLaux = eBotLeft;
			bbox[0] = bbox[1];
			bbox[1] = bbox0aux;
			eBotLeft = eTopRight;
			eTopRight = BLaux;
		}
		else if (rotation >= 225.f && rotation < 315.f) {
			glm::vec3 bbox0aux = bbox[0];
			glm::vec3 bbox1aux = bbox[1];
			bbox[0] = eTopRight;
			bbox[1] = eBotLeft;
			eBotLeft = bbox0aux;
			eTopRight = bbox1aux;
		}

	bool en0InsidePlayer = glm::all(glm::greaterThanEqual(bbox[0], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[0], playerBbox[1]));
	bool en1InsidePlayer = glm::all(glm::greaterThanEqual(bbox[1], playerBbox[0])) && glm::all(glm::lessThanEqual(bbox[1], playerBbox[1]));
	bool enTRInsidePlayer = glm::all(glm::greaterThanEqual(eTopRight, playerBbox[0])) && glm::all(glm::lessThanEqual(eTopRight, playerBbox[1]));
	bool enBLInsidePlayer = glm::all(glm::greaterThanEqual(eBotLeft, playerBbox[0])) && glm::all(glm::lessThanEqual(eBotLeft, playerBbox[1]));
	bool p0InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[0], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[0], bbox[1]));
	bool p1InsideEntity = glm::all(glm::greaterThanEqual(playerBbox[1], bbox[0])) && glm::all(glm::lessThanEqual(playerBbox[1], bbox[1]));
	bool pTRInsideEntity = glm::all(glm::greaterThanEqual(pTopRight, bbox[0])) && glm::all(glm::lessThanEqual(pTopRight, bbox[1]));
	bool pBLInsideEntity = glm::all(glm::greaterThanEqual(pBotLeft, bbox[0])) && glm::all(glm::lessThanEqual(pBotLeft, bbox[1]));
	return en0InsidePlayer || en1InsidePlayer || enTRInsidePlayer || enBLInsidePlayer || p0InsideEntity || p1InsideEntity || pTRInsideEntity || pBLInsideEntity;
}
