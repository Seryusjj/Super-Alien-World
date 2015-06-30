#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "BaseMenuLayer.h"

namespace Menus{
	class MainMenuLayer :public BaseMenuLayer
	{

	private:
		std::vector<std::function<void(Ref*)>> _functions;
		void selectMenuButton();
		void optionsButton();
		void actionButton1();
		void actionButton2();
		void actionButton3();
		void actionButton4();
		void actionButton5();
		void actionButton6();


	protected:
		void initFunctions(std::vector<std::function<void(Ref*)>>& functions);

	public:
		virtual bool init();
		static cocos2d::Scene* createScene();

		CREATE_FUNC(MainMenuLayer);
	};
}

#endif //__MAINMENULAYER_H__

