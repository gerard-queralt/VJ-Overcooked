#ifndef _FOOD_GENERATOR_INCLUDE
#define _FOOD_GENERATOR_INCLUDE

#include "Table.h"
#include "Food.h"

class FoodGenerator :
	public Table
{
public:
	bool init(ShaderProgram &program);

	void setFood(string food);

private:
	string generates;
};

#endif //_FOOD_GENERATOR_INCLUDE