#include "EnemyMouse.h"

using namespace Actors;

bool EnemyMouse::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemyMouse::setEnemyType(){
	_baseSpriteName = "mouse";
}

