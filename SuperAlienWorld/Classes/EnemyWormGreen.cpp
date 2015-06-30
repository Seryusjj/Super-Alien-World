#include "EnemyWormGreen.h"

using namespace Actors;

bool EnemyWormGreen::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemyWormGreen::setEnemyType(){
	_baseSpriteName = "wormGreen";
}

