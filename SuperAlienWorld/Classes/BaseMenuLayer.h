#ifndef __BASEMENULAYER_H__
#define __BASEMENULAYER_H__

#include "BackGround3Parts.h"
#include "cocos2d.h"

namespace Menus{
	class BaseMenuLayer :public cocos2d::Layer
	{
	protected:
		BackGround3Parts* _bg;
		cocos2d::Size _visibleSize;
		cocos2d::SpriteBatchNode* _gameBatchNode;

	public:
		BaseMenuLayer();
		virtual ~BaseMenuLayer();

		virtual void update(float dt);
		virtual bool init();

		static cocos2d::Scene* createScene();

		// implement the "static create()" method manually
		CREATE_FUNC(BaseMenuLayer);
	};
}

#endif

