#ifndef _LEVEL_FACTORY_INCLUDE
#define _LEVEL_FACTORY_INCLUDE

#include "Level.h"

class LevelFactory
{
public:
	LevelFactory() {}
	
	static LevelFactory &instance()
	{
		static LevelFactory LF;

		return LF;
	}

	Level* createLevel(int level, ShaderProgram texProgram);

private:
	Level* createLevel1(ShaderProgram texProgram);

	Level* createLevel2(ShaderProgram texProgram);

	Level* createLevel3(ShaderProgram texProgram);

	Level* createLevel4(ShaderProgram texProgram);

	Level* createLevel5(ShaderProgram texProgram);
};

#endif //_LEVEL_FACTORY_INCLUDE