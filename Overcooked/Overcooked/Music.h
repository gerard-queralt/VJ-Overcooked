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

private:
	ISoundEngine* engine;
	ISound* music;

	void setVolume();
};

#endif //_MUSIC_INCLUDE