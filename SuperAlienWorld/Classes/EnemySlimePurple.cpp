#include "EnemySlimePurple.h"





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
