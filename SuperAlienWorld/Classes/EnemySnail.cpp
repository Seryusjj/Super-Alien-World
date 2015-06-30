#include "EnemySnail.h"

using namespace Actors;

bool EnemySnail::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemySnail::setEnemyType(){
	_baseSpriteName = "snail";
}

