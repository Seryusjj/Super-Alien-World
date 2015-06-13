#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"





class Player;

class BaseLevel : public cocos2d::Layer
{

private:
	cocos2d::ui::Button* _backBt;
	cocos2d::ui::Button* _respawnButton;
	cocos2d::Size _visibleSize;
	cocos2d::TMXTiledMap * _map;
	Player * _player;
	cocos2d::Follow* _camera;
	cocos2d::Node* _cameraTarget;

protected:

	std::string _levelName;
	std::string _bgName;
	virtual void setLevel();
	virtual void respawnButtonAction();

private:
	void createWinningArea();
	void createWall();
	void initCamera();
	void createGround();
	void createEnemies();
	void initVariables();
	void createBackground();
	void levelCompleteActions();
	void levelCompleteActionsHelper();
	void createRespawnButton();
	void createBackButton(); 
	void actionButtonBack();

private:
	cocos2d::Point tileCoordinateToCocosPosition(cocos2d::Size layerPosition, cocos2d::Point tileCoordinate);
	void createPhysicsBodyFromPoints(cocos2d::Point& origin, cocos2d::Point& destination, int tag);

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(BaseLevel);
};

