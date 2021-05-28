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

	void playSoundEffect(int sound);
	void stopSoundEffect(int sound);

private:
	ISoundEngine* engine;
	ISound* cutting; //1
	ISound* alarm; //2
	ISound* steps; //3
	ISound* arrow; //4
	ISound* clock; //5
	ISound* pick; //6
	ISound* stove; //7
	ISound* corDish; //8
	ISound* incDish; //9
	ISound* burning; //10
	ISound* music;

	void setVolume(int vol);
};

#endif //_MUSIC_INCLUDE