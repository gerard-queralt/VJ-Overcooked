#include "Music.h"



Music::Music()
{
	engine = createIrrKlangDevice();
	effect = createIrrKlangDevice();
}


Music::~Music()
{
}

void Music::playMenuMusic()
{
	music = engine->play2D("music/mainMenu.mp3",true,false,true);
	setVolume(1);
}

void Music::playGameMusic(int level)
{
	switch (level)
	{
	case 1: music = engine->play2D("music/firstLevel.mp3", true, false, true);
		break;
	case 2: music = engine->play2D("music/secondLevel.mp3", true, false, true);
		break;
	case 3: music = engine->play2D("music/thirdLevel.mp3", true, false, true);
		break;
	case 4: music = engine->play2D("music/fourthLevel.mp3", true, false, true);
		break;
	case 5: music = engine->play2D("music/fifthLevel.mp3", true, false, true);
		break;
	default:
		break;
	}
	setVolume(0);
}

void Music::stopMusic()
{
	music->stop();
}

void Music::playSoundEffect()
{
	effect->play2D("music/cutting.mp3", true, false, true, ESM_AUTO_DETECT, true);
}

bool Music::validSoundEffect()
{
	return effect;
}

void Music::stopSoundEffect()
{
	effect->stopAllSounds();
}

void Music::setVolume(int vol)
{
	if (vol == 1)
		music->setVolume(0.3);
	else
		music->setVolume(0.05);
}

