#include "EnemySlimeBlue.h"

using namespace Actors;

bool EnemySlimeBlue::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemySlimeBlue::setEnemyType(){
	_baseSpriteName = "slimeBlue";
}

