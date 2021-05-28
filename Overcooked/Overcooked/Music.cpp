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

void Music::playSoundEffect(int sound)
{
	switch (sound)
	{
	case 1:
		cutting = engine->play2D("music/cutting.mp3", true, false, true);
		break;
	case 2:
		alarm = engine->play2D("music/alarm.mp3", true, false, true);
		break;
	case 3:
		steps = engine->play2D("music/footsteps.mp3", true, false, true);
		steps->setVolume(0.15);
		break;
	case 4:
		arrow = engine->play2D("music/arrow.mp3", false, false, true);
		arrow->setVolume(0.02);
		break;
	case 5:
		clock = engine->play2D("music/foodReady.mp3", false, false, true);
		break;
	case 6:
		pick = engine->play2D("music/pickItem.mp3", false, false, true);
		break;
	case 7:
		stove = engine->play2D("music/stove.mp3", true, false, true);
		break;
	case 8:
		corDish = engine->play2D("music/correct.mp3", false, false, true);
		break;
	case 9:
		incDish = engine->play2D("music/incorrect.mp3", false, false, true);
		break;
	default:
		break;
	}
}


void Music::stopSoundEffect(int sound)
{
	switch (sound)
	{
	case 1: 
		if (cutting) {
			cutting->stop();
		}
		break;
	case 2:
		if (alarm) {
			alarm->stop();
		}
		break;
	case 3:
		if (steps) {
			steps->stop();
		}
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		if (stove) {
			stove->stop();
		}
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}
}

void Music::setVolume(int vol)
{
	if (vol == 1)
		music->setVolume(0.3);
	else
		music->setVolume(0.05);
}

