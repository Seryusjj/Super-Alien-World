#include "EnemyFactory.h"
#include "EnemyFrog.h"
#include "EnemyLadybug.h"
#include "EnemySlimeBlue.h"
#include "EnemySlimePurple.h"
#include "EnemySlimeGreen.h"
#include "EnemyWormGreen.h"
#include "EnemySnail.h"
#include "EnemyMouse.h"

using namespace Levels;
using namespace Actors;

EnemyFactory* EnemyFactory::_instance = nullptr;
EnemyFactory::EnemyFactory(){}

EnemyFactory* EnemyFactory::getInstance(){
	if (_instance == nullptr){
		_instance = new EnemyFactory();
	}
	return _instance;
}

Enemy* EnemyFactory::getEnemy(int tileGID){
	switch (tileGID)
	{
	case WORM_PINK:		return Enemy::create();
	case FROG:			return EnemyFrog::create();
	case LADYBUG:		return EnemyLadybug::create();
	case SLIME_BLUE:	return EnemySlimeBlue::create();
	case SLIME_PURPLE:	return EnemySlimePurple::create();
	case WORM_GREEN:	return EnemyWormGreen::create();
	case MOUSE:			return EnemyMouse::create();
	case SLIME_GREEN:	return EnemySlimeGreen::create();;
	case SNAIL:			return EnemySnail::create();
	default:			return Enemy::create();
	}

}
