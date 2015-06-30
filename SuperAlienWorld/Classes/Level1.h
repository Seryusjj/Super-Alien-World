#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"


namespace Actors{
	class Player;
}

namespace Levels{
	class Level1 : public cocos2d::Layer
	{

	private:
		cocos2d::ui::Button* _backBt;
		cocos2d::ui::Button* _respawnButton;
		cocos2d::Size _visibleSize;
		cocos2d::TMXTiledMap * _map;
		Actors::Player * _player;
		cocos2d::Follow* _camera;
		cocos2d::Node* _cameraTarget;

	protected:

		std::string _levelName;
		std::string _bgName;
		virtual void setLevel();
		virtual void respawnButtonAction();

	private:
		void createPhysicsFromLayer(std::string layerName, int tag);


		void initCamera();

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
		CREATE_FUNC(Level1);
	};
}

