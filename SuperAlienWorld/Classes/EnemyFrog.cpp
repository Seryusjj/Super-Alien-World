#include "EnemyFrog.h"

using namespace Actors;
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
