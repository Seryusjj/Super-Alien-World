#include "EnemyLadybug.h"

using namespace Actors;

bool EnemyLadybug::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemyLadybug::setEnemyType(){
	_baseSpriteName = "ladybug";
}
