#include "Trash.h"

//no fa res perque no existeix un  model separat del plat
bool Trash::init(ShaderProgram & program)
{
	return true;
}

string Trash::whatAmI()
{
	return "Trash";
}
