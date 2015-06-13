#pragma once
#include "BaseLevel.h"

class Level2: public BaseLevel
{
protected:
	virtual void setLevel() override;
	virtual void respawnButtonAction() override;
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(Level2);
};

