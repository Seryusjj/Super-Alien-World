#pragma once
#include "Level1.h"
namespace Levels{
	class Level2 : public Level1
	{
	protected:
		virtual void setLevel() override;
		virtual void respawnButtonAction() override;
	public:
		static cocos2d::Scene* createScene();
		virtual bool init() override;
		CREATE_FUNC(Level2);
	};
}

