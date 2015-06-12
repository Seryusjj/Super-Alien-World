#include "EnemySlimeBlue.h"

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

