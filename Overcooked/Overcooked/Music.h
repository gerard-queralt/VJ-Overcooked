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

private:
	ISoundEngine* engine;
};

#endif //_MUSIC_INCLUDE