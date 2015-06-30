#include "GameManager.h"


USING_NS_CC;
using namespace Levels;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager(){}


GameManager::~GameManager()
{
}

GameManager*  GameManager::getInstance(){

	if (!_instance){
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::saveGame(int tag){
	if (tag > getNextLevel())
	{
		UserDefault::getInstance()->setIntegerForKey(LEVELKEY, tag);
	}
}

int GameManager::getNextLevel(){
	return UserDefault::getInstance()->getIntegerForKey(LEVELKEY, 0);
}

