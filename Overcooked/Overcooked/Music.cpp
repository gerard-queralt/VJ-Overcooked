#include "Music.h"



Music::Music()
{
	engine = createIrrKlangDevice();
}


Music::~Music()
{
}

void Music::playMenuMusic()
{
	engine->play2D("music/mainMenu.mp3",true);
}