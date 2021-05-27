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
	music = engine->play2D("music/mainMenu.mp3",true,false,true);
	setVolume();
}

void Music::playGameMusic(int level)
{
	switch (level)
	{
	case 1: music = engine->play2D("music/firstLevel.mp3", true, false, true, ESM_AUTO_DETECT, true);
		break;
	case 2: music = engine->play2D("music/secondLevel.mp3", true, false, true, ESM_AUTO_DETECT, true);
		break;
	case 3: music = engine->play2D("music/thirdLevel.mp3", true, false, true, ESM_AUTO_DETECT, true);
		break;
	case 4: music = engine->play2D("music/fourthLevel.mp3", true, false, true, ESM_AUTO_DETECT, true);
		break;
	case 5: music = engine->play2D("music/fifthLevel.mp3", true, false, true, ESM_AUTO_DETECT, true);
		break;
	default:
		break;
	}
	setVolume();
}

void Music::stopMusic()
{
	music->stop();
}

void Music::setVolume()
{
	music->setVolume(0.5);
}

