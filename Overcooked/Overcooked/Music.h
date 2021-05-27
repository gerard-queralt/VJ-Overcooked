#ifndef _MUSIC_INCLUDE
#define _MUSIC_INCLUDE

#include "irrKlang.h"
using namespace irrklang;

class Music
{
public:
	Music();

	static Music &instance()
	{
		static Music M;

		return M;
	}

	~Music();
	void playMenuMusic();
	void playGameMusic(int level);
	void stopMusic();

	void playSoundEffect();
	bool validSoundEffect();
	void stopSoundEffect();

private:
	ISoundEngine* engine;
	ISoundEngine* effect;
	ISound* music;

	void setVolume(int vol);
};

#endif //_MUSIC_INCLUDE