#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "BaseMenuLayer.h"

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
	void actionButton7();
	void actionButton8();
	void actionButton9();

protected:
	void initFunctions(std::vector<std::function<void(Ref*)>>& functions);
	
public:
	virtual bool init();
	static cocos2d::Scene* createScene();

	CREATE_FUNC(MainMenuLayer);
};

#endif //__MAINMENULAYER_H__

