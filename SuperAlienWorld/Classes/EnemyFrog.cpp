#include "EnemyFrog.h"


bool EnemyFrog::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	return true;
}

void EnemyFrog::setEnemyType(){
	_baseSpriteName = "frog";
}
