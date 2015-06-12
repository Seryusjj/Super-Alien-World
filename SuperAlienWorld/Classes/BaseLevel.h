#pragma once

#include "cocos2d.h"





class Player;

class BaseLevel : public cocos2d::Layer
{
protected:
	cocos2d::Size _visibleSize;
	cocos2d::TMXTiledMap * _map;
	Player * _player;
	cocos2d::Follow* _camera;
	cocos2d::Node* _cameraTarget;
	std::string _levelName;
	std::string _bgName;
	void setLevel();

private:
	void createWinningArea();
	void initCamera();
	void createGround();
	void createEnemies();
	void initVariables();
	void createBackground();
private:
	cocos2d::Point tileCoordinateToCocosPosition(cocos2d::Size layerPosition, cocos2d::Point tileCoordinate);
	void createPhysicsBodyFromPoints(cocos2d::Point& origin, cocos2d::Point& destination, int tag);

public:

	static cocos2d::Scene* createScene();


	virtual bool init();

	void update(float dt);

	CREATE_FUNC(BaseLevel);
};

