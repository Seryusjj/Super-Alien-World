#include "EnemySlimePurple.h"


using namespace Actors;


bool EnemySlimePurple::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemySlimePurple::setEnemyType(){
	_baseSpriteName = "slimePurple";
}
