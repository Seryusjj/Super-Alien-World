#include "EnemySlimeGreen.h"

using namespace Actors;

bool EnemySlimeGreen::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemySlimeGreen::setEnemyType(){
	_baseSpriteName = "slimeGreen";
}
