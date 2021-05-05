#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	//Lectura inputs
	if (keys['w'])
		scene.movePlayer(scene.FRONT);
	if (keys['s'])
		scene.movePlayer(scene.BACK);
	if (keys['a'])
		scene.movePlayer(scene.LEFT);
	if (keys['d'])
		scene.movePlayer(scene.RIGHT);

	if (keys['1'])
		scene.changeCamera(scene.FP);
	else if (keys['2'])
		scene.changeCamera(scene.CAM_1);
	else if (keys['3'])
		scene.changeCamera(scene.CAM_2);
	else if (keys['4'])
		scene.changeCamera(scene.CAM_3);
	else if (keys['5'])
		scene.changeCamera(scene.CAM_4);
	else if (keys['6']) {
		scene.changeCamera(scene.TP);
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





